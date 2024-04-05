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
    pwm_oc2(FREQ_1350,50);
    
    SET_GLOBAL_INTERRUPT;
    uart_init();

    uint16_t freq = 0;
    uint8_t dc = 0;

    for(;;)
    {
        freq = measure_frequency();
        dc = measure_dutycycle();
        
        uart_send_string("frequency: ");
        uart_send_integer(freq);
        uart_send_string("\nduty cycle: ");
        uart_send_integer(dc);
        uart_send_string("%\n");
        ms_delay(5000);
    }
}