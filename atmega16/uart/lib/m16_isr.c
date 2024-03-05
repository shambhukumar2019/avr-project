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
// #include "m16_uart.h"

/* volatile uint16_t f1 = 0;
volatile uint16_t f2 = 0;
static uint8_t count = 0; */

/* uint8_t data[3];
uint8_t i = 0;
uint8_t j = 0; */
// uint8_t byte = 0;

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
    /* f1 = ICR1;
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
    } */
}

ISR(USART_UDRE_vect)
{
    UDR = byte;
    /* UDR = data[i++];
    if(i>=2)
    {
        i = 0;
    } */
    DISABLE_UART_UDRE_INTERRUPT;
}

ISR(USART_RXC_vect)
{
    byte = UDR;
    data = byte;
    /* data[j++] = UDR;
    value[0] = data[--j];
    if(j>=2)
    {
        j = 0;
    } */

    ENABLE_UART_UDRE_INTERRUPT;
}

ISR(BADISR_vect)
{
    
}


