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
    uint8_t data = 0;

    SET_GLOBAL_INTERRUPT;

    uart_init();

    keypad_init();

    uart_send_string("!!!-------KEYPAD SCANNING ON-------!!!\n");
    
    for(;;)
    {
        data = keypad_scan();

        if(data != 0xff)
        {
            uart_send_string("button pressed: ");
            uart_send_byte(data);
            uart_send_byte('\n');
        }

        _delay_ms(10);
    }
}
