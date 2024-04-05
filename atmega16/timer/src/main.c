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
    GPIO_PULLUP_ON(PORTD,T1_ICP_PIN);
    gpio_pin_mode(T1_ICP_PIN,&PORTD,INPUT);
    
    ENABLE_INPUT_CAPTURE;
    

    
    uint16_t f = 0;

    // measure frequency using ICP of timer 1
    while ((TIFR & (1<<ICF1)) == 0);
    f = ICR1;
    CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);

    while ((TIFR & (1<<ICF1)) == 0);
    f = ICR1 - f;
    // CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);
    
    SET_GLOBAL_INTERRUPT;
    uart_init();


    for(;;)
    {
        uart_send_integer(f);
        uart_send_byte('\n');
        ms_delay(2000);
        
    }
}