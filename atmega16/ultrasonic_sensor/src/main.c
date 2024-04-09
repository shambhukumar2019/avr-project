/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief main driver code
 * @version 0.1
 * @date 2024-03-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "common.h"



void main(void)
{
    gpio_pin_mode(TRIG_PIN,&TRIG_PORT,OUTPUT);

    volatile uint16_t l_icp_cnt_1 = 0;
    volatile uint16_t l_icp_cnt_2 = 0;
    volatile uint32_t l_icp_cnt_3 = 0;

    SET_GLOBAL_INTERRUPT;
    uart_init();
    ENABLE_INTERRUPT(TIMER_INTERRUPT_REG,T1_OVERFLOW_INTERRUPT);

    for(;;)
    {
        SEND_TRIGGER_PULSE;

        gpio_pin_mode(ECHO_PIN,&ECHO_PORT,INPUT);

        TCNT1 = 0;

        // measure duty cycle using ICP of timer 1
        ENABLE_ICP_RISE_EDGE;

        //  get 1st timestamp of rising edge 
        while (POLL_BIT(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG) == 0);
        l_icp_cnt_1 = ICR1;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);

        ENABLE_ICP_FALL_EDGE;

        //  get 1st timestamp of falling edge 
        while (POLL_BIT(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG) == 0);
        l_icp_cnt_2 = ICR1;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);

        DISABLE_ICP;
        
        l_icp_cnt_3 = ((l_icp_cnt_2 + (overflow_counter * 65535UL)) - l_icp_cnt_1);
        
        overflow_counter = 0;

        l_icp_cnt_3 = (16U * l_icp_cnt_3);
        l_icp_cnt_3 /= 10000U;

        uart_send_string("Object at = ");
        uart_send_integer(l_icp_cnt_3);
        uart_send_string(" cm\n");
        ms_delay(2000);
    }
}
