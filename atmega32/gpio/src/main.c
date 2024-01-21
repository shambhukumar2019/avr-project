/**
 * @file main.c
 * @author shambhu kumar (you@domain.com)
 * @brief driver code for gpio library
 * @version 1.0
 * @date 2024-01-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "m16_gpio.h"


/**
 * @brief define when debuggind with simavr simulator
 * 
 */
//#define SIMAVR

#ifndef F_CPU
/**
 * @brief set clock frequency for CPU
 * 
 */
#define F_CPU 11059200UL
#endif

#include<util/delay.h>


/**
 * @brief main driver code for m32_gpio
 * 
 */
void main(void)
{
    gpio_pin_mode(PIN0,PORTA,OUT);
    gpio_pin_mode(PIN1,PORTA,IN);
    gpio_pullup_on(PIN1,PORTA);

    
    for(;;)
    {
        if (gpio_read(PIN1,PORTA))
        {
            gpio_set_output_pin_value(PIN0,PORTA,VCC);
            #ifndef SIMAVR
            _delay_ms(1000);
            #endif
            gpio_set_output_pin_value(PIN0,PORTA,GND);
            #ifndef SIMAVR
            _delay_ms(1000);
            #endif
        }
        else
        {
            gpio_set_output_pin_value(PIN0,PORTA,VCC);
            #ifndef SIMAVR
            _delay_ms(300);
            #endif
            gpio_set_output_pin_value(PIN0,PORTA,GND);
            #ifndef SIMAVR
            _delay_ms(300);
            #endif
        }
    }
    
}