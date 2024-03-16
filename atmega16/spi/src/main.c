/**
 * @file main.c
 * @author shambhu kumar (you@domain.com)
 * @brief driver code for SPI
 * @version 0.1
 * @date 2024-03-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "common.h"



void main(void)
{
    uint16_t voltage = 0;   // store voltage read from mcp3208 ADC

    SET_GLOBAL_INTERRUPT;

    uart_init();    // initiallize UART

    adc_init_mcp3208(); // initialize MCP3208 ADC

    for(;;)
    {
        voltage = (uint16_t)read_millivolt_mcp3208(ADC_MCP3208_CHANNEL_0);
        uart_send_string("ADC digital Value: ");
        uart_send_integer(adc_value_mcp3208);
        uart_send_string("\n");

        uart_send_string("Voltage: ");
        uart_send_integer(voltage);
        uart_send_string("mV\n");

        _delay_ms(1000);
    }
}
