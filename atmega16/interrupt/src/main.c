/**
 * @file main.c
 * @author shambhu kumar (you@domain.com)
 * @brief driver file for interrupt library
 * @version 0.1
 * @date 2024-01-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "m16_interrupt.h"
#include "m16_gpio.h"

#include "util/delay.h"



/**
 * @brief main driver code
 * 
 */
void main(void)
{
    gpio_pin_mode(PD2,&PORTD,IN);
    gpio_pin_mode(PA0,&PORTA,OUT);
    gpio_pullup_on(PD2,&PORTD);
    config_interrupt(EXTERNAL_INTERRUPT_0,ENABLE,ANY_LOGIC_CHANGE);
    gpio_set_output_pin_value(PA0,&PORTA,VCC);
    SET_GLOBAL_INTERRUPT;
    
    for(;;)
    {
        _delay_ms(1000);
        gpio_set_output_pin_value(PA0,&PORTA,VCC);
        _delay_ms(1000);
        gpio_set_output_pin_value(PA0,&PORTA,GND);
    }

}