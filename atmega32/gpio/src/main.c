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

#include "m32_gpio.h"

#define SIMAVR

#ifndef F_CPU
/// define clock frequency for CPU
#define F_CPU 1000000UL
#endif

#include<util/delay.h>


/**
 * @brief main driver code for m32_gpio
 * 
 */
void main(void)
{
    gpio_setout(PIN0,PORTA);

    /// never ending loop
    while(1)
    {
        gpio_set_output(PIN0,PORTA,VCC);
        #ifndef SIMAVR
        _delay_ms(1000);
        #endif
        gpio_set_output(PIN0,PORTA,GND);
        #ifndef SIMAVR
        _delay_ms(1000);
        #endif
    }
    
}