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
    uart_init(BAUD_9600);   // initiallize uart with given baud rate

    //gpio
    gpio_port_mode(&PORTA,OUTPUT);
    // GPIO_PIN_HIGH(PORTA,PA0);
    SET_GLOBAL_INTERRUPT;

    for(;;)
    {
        if((value[0] - 48) >= 5 )
            PORTA = 0xff;
        else
            PORTA = 0x00;
        
        // if(value[0] == 1)
        // {
            // GPIO_PIN_HIGH(PORTA,PA0);
        // }
        // else if(value[0] == 0)
        // {
            // GPIO_PIN_LOW(PORTA,PA0);
        // }
        // eternal loop
    }
}