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

volatile uint16_t f1 = 0;
volatile uint16_t f2 = 0;
static uint8_t count = 0;

ISR(INT0_vect)
{
    // GPIO_OUTPUT_HIGH(PORTA,PA0);
}

ISR(TIMER0_OVF_vect)
{
    /* count++;
    if(count >= 50)
    {
        count = 0;
        GPIO_PIN_TOGGLE(PORTA,PIN0);
    }
    TCNT0 = 0x00; */
    // GPIO_PIN_TOGGLE(PORTA,PIN0);
    // TCNT0 = 250;
}

ISR(TIMER0_COMP_vect)
{
    //OCR0 = 250;
}

ISR(TIMER1_COMPA_vect)
{
      
    
}

ISR(TIMER1_CAPT_vect)
{
    f1 = ICR1;
    if (count == 0)
    {
        f2 = f1;
        count++;
    }
    else
    {
        count = 0;
        f2 = f1 - f2;
        TIMSK &= ~(1<<TICIE1);
    }
}

ISR(BADISR_vect)
{
    
}


