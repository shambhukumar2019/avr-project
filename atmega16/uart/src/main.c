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
        if((data - 48) == 1 )
            PORTA = 0xff;
        else if((data - 48) == 0)
            PORTA = 0x00;
        else if((data - 48) >=5)
        {
            PORTA = 1;
            _delay_ms(1000);
            PORTA = 2;
            _delay_ms(1000);
            PORTA = 4;
            _delay_ms(5000);
            PORTA = 8;
            _delay_ms(1000);
            PORTA = 16;
            _delay_ms(1000);
            PORTA = 32;
            _delay_ms(1000);
            PORTA = 64;
            _delay_ms(1000);
            PORTA = 128;
            _delay_ms(1000);
        }
        
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