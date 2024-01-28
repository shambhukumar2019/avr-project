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
    gpio_pin_mode(EXT_INTRRUPT_0_PIN,&PORTD,IN);
    gpio_pin_mode(PA0,&PORTA,OUT);

    config_interrupt(EXTERNAL_INTERRUPT_0,ENABLE,ANY_LOGIC_CHANGE);

    SET_GLOBAL_INTERRUPT;
    
    for(;;)
    {
        _delay_ms(1000);
        GPIO_OUTPUT_HIGH(PORTA,PA0);
        _delay_ms(1000);
        GPIO_OUTPUT_LOW(PORTA,PA0);
    }

}