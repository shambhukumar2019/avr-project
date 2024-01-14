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

#include "m32_gpio.h"


#define SET_BIT(r,b)        (r |= (1<<b))
#define RESET_BIT(r,b)      (r &= ~(1<<b))

/**
 * @brief define gpio_mode() 
 * 
 * @param pin 
 * @param port 
 * @param io_mode 
 */
void gpio_mode(volatile uint8_t pin,volatile uint8_t port,volatile uint8_t io_mode)
{
    if (io_mode == OUT)
    {
        if(PORTA == port)
            SET_BIT(DDRA,pin);
        

        else if(PORTB == port)
            SET_BIT(DDRB,pin);
            
        
        else if(PORTC == port)
            SET_BIT(DDRC,pin);
            

        else if (PORTD == port)    
            SET_BIT(DDRD,pin);
    }
    else if (io_mode == IN)
    {
        if(PORTA == port)
            RESET_BIT(DDRA,pin);

        else if(PORTB == port)
            RESET_BIT(DDRB,pin);
        
        else if(PORTC == port)
            RESET_BIT(DDRC,pin);

        else if (PORTD == port)    
            RESET_BIT(DDRD,pin);
    }    

}

/**
 * @brief define gpio_set_output()
 * 
 * @param pin 
 * @param port 
 * @param logic 
 */
void gpio_set_output_value(volatile uint8_t pin,volatile uint8_t port,volatile uint8_t logic)
{
    if(PORTA == port)
    {
        if (logic == VCC)
        {
            SET_BIT(PORTA,pin);
        }
        else if(logic == GND)
        {
            RESET_BIT(PORTA,pin);
        }
        else
        {
            // through error code
        }
    }
        

    else if(PORTB == port)
    {
        if (logic == VCC)
        {
            SET_BIT(PORTB,pin);
        }
        else if(logic == GND)
        {
            RESET_BIT(PORTB,pin);
        }
        else
        {
            // through error code
        }
    }

    else if(PORTC == port)
    {
        if (logic == VCC)
        {
            SET_BIT(PORTC,pin);
        }
        else if(logic == GND)
        {
            RESET_BIT(PORTC,pin);
        }
        else
        {
            // through error code
        }
    }

    else if(PORTD == port)
    {
        if (logic == VCC)
        {
            SET_BIT(PORTD,pin);
        }
        else if(logic == GND)
        {
            RESET_BIT(PORTD,pin);
        }
        else
        {
            // through error code
        }
    }
}


/**
 * @brief define gpio_pullup_on()
 * 
 * @param pin 
 * @param port 
 */
void gpio_pullup_on(volatile uint8_t pin,volatile uint8_t port)
{
    if(PORTA == port)
        
        SET_BIT(PORTA,pin);

    else if(PORTB == port)

        SET_BIT(PORTB,pin);
    
    else if(PORTC == port)

        SET_BIT(PORTC,pin);

    else if (PORTD == port)    

        SET_BIT(PORTD,pin);
}


/**
 * @brief define gpio_pullup_off()
 * 
 * @param pin 
 * @param port 
 */
void gpio_pullup_off(volatile uint8_t pin,volatile uint8_t port)
{
    if(PORTA == port)
        
        RESET_BIT(PORTA,pin);

    else if(PORTB == port)

        RESET_BIT(PORTB,pin);
    
    else if(PORTC == port)

        RESET_BIT(PORTC,pin);

    else if (PORTD == port)    

        RESET_BIT(PORTD,pin);
}


/**
 * @brief define gpio_global_pullup_disable
 * 
 */
void gpio_global_pullup_disable(void)
{
    SET_BIT(SFIOR,PUD);
}


/**
 * @brief define gpio_global_pullup_enable
 * 
 */
void gpio_global_pullup_enable(void)
{
    RESET_BIT(SFIOR,PUD);
}


/**
 * @brief define gpio_read()
 * 
 * @param pin 
 * @param port 
 * @return volatile uint8_t
 */
volatile uint8_t gpio_read(volatile uint8_t pin,volatile uint8_t port)
{
    if(PORTA == port)
    {
        asm("nop");
        return (PINA & (1<<pin));
    }

    else if(PORTB == port)
    {
        asm("nop");
        return (PINB & (1<<pin));
    }

    else if (PORTC == port)
    {
        asm("nop");
        return (PINC & (1<<pin));
    }

    else if(PORTD == port)
    {
        asm("nop");
        return (PIND & (1<<pin));
    }
    else
    {
        return 0;
    }

}