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
    gpio_pin_mode(PD7,&PORTD,OUTPUT);
    volatile uint32_t l_icp_cnt_1 = 0;

    SET_GLOBAL_INTERRUPT;
    uart_init();

    for(;;)
    {
        GPIO_PIN_HIGH(PORTD,PD7);
        _delay_us(20);
        GPIO_PIN_LOW(PORTD,PD7);

        gpio_pin_mode(T1_ICP_PIN,&PORTD,INPUT);

        // measure duty cycle using ICP of timer 1
        ENABLE_ICP_RISE_EDGE;

        //  get 1st timestamp of rising edge 
        while ((TIFR & (1<<ICF1)) == 0);
        l_icp_cnt_1 = ICR1;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);

        ENABLE_ICP_FALL_EDGE;

        //  get 1st timestamp of falling edge 
        while ((TIFR & (1<<ICF1)) == 0);
        l_icp_cnt_1 = ICR1 - l_icp_cnt_1;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);

        DISABLE_ICP;

        // uart_send_integer(l_icp_cnt_1);
        // uart_send_byte('\n');

        l_icp_cnt_1 = (16U * l_icp_cnt_1) / 1000U;

        uart_send_string("distance = ");
        uart_send_integer(l_icp_cnt_1 + 5);
        uart_send_string(" mm\n");
        ms_delay(2000);
    }
}