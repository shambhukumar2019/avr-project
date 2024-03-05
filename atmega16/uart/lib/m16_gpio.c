/**
 * @file m32_gpio.c
 * @author shambhu kumar (you@domain.com)
 * @brief source file for atmega32 gpio operations
 * @version 1.0
 * @date 2024-01-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "m16_gpio.h"



/**
 * @brief define gpio_mode() 
 * 
 * @param pin 
 * @param port 
 * @param io_mode 
 */
void gpio_pin_mode(uint8_t pin,volatile uint8_t *port,uint8_t io_mode)
{
    if (io_mode == OUTPUT)
    {
        if(&PORTA == port)
        {
            SET_BIT(DDRA,pin);
        }
        else if(&PORTB == port)
        {
            SET_BIT(DDRB,pin);
        }
        else if(&PORTC == port)
        {
            SET_BIT(DDRC,pin);
        }
        else if (&PORTD == port)    
        {
            SET_BIT(DDRD,pin);
        }
    }
    else if (io_mode == INPUT)
    {
        if(&PORTA == port)
        {
            CLEAR_BIT(DDRA,pin);
        }
        else if(&PORTB == port)
        {
            CLEAR_BIT(DDRB,pin);
        }
        else if(&PORTC == port)
        {
            CLEAR_BIT(DDRC,pin);
        }
        else if (&PORTD == port)    
        {
            CLEAR_BIT(DDRD,pin);
        }
    }
}


void gpio_port_mode(volatile uint8_t *port,uint8_t io_mode)
{
    if (io_mode == OUTPUT)
    {
        if(&PORTA == port)
        {
            DDRA = 0xff;
        }
        else if(&PORTB == port)
        {
            DDRB = 0xff;
        }
        else if(&PORTC == port)
        {
            DDRC = 0xff;
        }
        else if (&PORTD == port)    
        {
            DDRD = 0xff;
        }
    }
    else if (io_mode == INPUT)
    {
        if(&PORTA == port)
        {
            DDRA = 0x00;
        }
        else if(&PORTB == port)
        {
            DDRB = 0x00;
        }
        else if(&PORTC == port)
        {
            DDRC = 0x00;
        }
        else if (&PORTD == port)    
        {
            DDRD = 0x00;
        }
    }
}


/**
 * @brief define gpio_read()
 * 
 * @param pin_number
 * @param pin 
 * 
 * @return uint8_t
 */
inline uint8_t gpio_read(uint8_t pin_number,volatile uint8_t *pin)
{
    //asm("nop");
    __asm__("nop");
    return ((*pin) & (1<<pin_number));
}