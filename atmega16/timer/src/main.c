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
    pwm_oc2(FREQ_43200,50); // generate 43200 Hz freq. pwm with 50 % DC on OC2 pin

    //  input capture mode
    // GPIO_PULLUP_ON(PORTD,T1_ICP_PIN);
    gpio_pin_mode(T1_ICP_PIN,&PORTD,INPUT);
    
    ENABLE_ICP_RISE_EDGE;
    

    
    uint16_t f = 0,h = 0,t = 0;
    uint32_t dc = 0;

    // measure frequency using ICP of timer 1
    while ((TIFR & (1<<ICF1)) == 0);
    f = ICR1;
    CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);

    ENABLE_ICP_FALL_EDGE;

    while ((TIFR & (1<<ICF1)) == 0);
    h = ICR1;
    CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);

    ENABLE_ICP_RISE_EDGE;


    while ((TIFR & (1<<ICF1)) == 0);
    t = ICR1;
    // CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);
    dc = h - f;
    dc = dc * 100U;
    f = t - f;
    dc = dc / f;

    
    f = F_CPU / f;
    
    SET_GLOBAL_INTERRUPT;
    uart_init();


    for(;;)
    {
        uart_send_integer(f);
        uart_send_byte(',');
        uart_send_integer(dc);
        // uart_send_byte(',');
        // uart_send_integer(t);
        uart_send_byte('\n');
        ms_delay(2000);
        
    }
}