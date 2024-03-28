/**
 * @file main.c
 * @author shambhu kumar (you@domain.com)
 * @brief main driver code for uart
 * @version 0.1
 * @date 2024-02-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "m16_uart.h"


void main(void)
{
    uart_init();   // initiallize uart with given baud rate

    //gpio
    gpio_port_mode(&PORTA,OUTPUT);
    // GPIO_PIN_HIGH(PORTA,PA0);
    SET_GLOBAL_INTERRUPT;

    uart_send_string("my name is shambhu kumar\n");
    uart_send_string("shambhu kumar\n");

    for(;;)
    {
        uart_send_string("hello this is me into font\n");
        uart_send_string("one two ka four four two ka one\n");
        uart_send_string("my name is shambhu kumar\n");
        uart_send_string("Embedded Firmware Engineer\n");
        if(uart.uart_rx_complete_flag == 1)
        {
            uart_send_string(uart.uart_buffer);
        }
        _delay_ms(1000);
    }
}