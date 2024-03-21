/**
 * @file main.c
 * @author shambhu kumar (you@domain.com)
 * @brief driver code for I2C
 * @version 0.1
 * @date 2024-03-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "common.h"



void main(void)
{
    uint16_t voltage = 0;

    adc_init(ADC_CHANNEL); // ADC with atuo trigger on T1 compare match
    uart_init();

    SET_GLOBAL_INTERRUPT;
    
    
    for(;;)
    {
        voltage = adc_read();     // read adc every TIME_TO_GET_ADC_VOLT seconds

        uart_send_string("\nVoltage => ");
        uart_send_integer(millivolt_value);
        uart_send_string(" mV");

        battery_status();    // print percentage and status

        _delay_ms(2000);
    }
}
