/**
 * @file m16_isr.c
 * @author shambhu kumar (you@domain.com)
 * @brief define all ISR(interrupt sub-routines) in this file
 * @version 0.1
 * @date 2024-01-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "m16_interrupt.h"


volatile uint8_t count = 0;


ISR(INT0_vect)
{
    GPIO_OUTPUT_HIGH(PORTA,PA0);
}

ISR(TIMER0_OVF_vect)
{
    count++;
    if(count >= 50)
    {
        count = 0;
        GPIO_PIN_TOGGLE(PORTA,PIN0);
    }
    TCNT0 = 0x00;
}

ISR(TIMER0_COMP_vect)
{
    count++;
    if(count >= 50)
    {
        count = 0;
        GPIO_PIN_TOGGLE(PORTA,PIN0);
    } 

}

ISR(BADISR_vect)
{
    
}


