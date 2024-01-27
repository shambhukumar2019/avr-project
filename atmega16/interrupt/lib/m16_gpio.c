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
void gpio_pin_mode(volatile uint8_t pin,volatile uint8_t *port,volatile uint8_t io_mode)
{
    if (io_mode == OUT)
    {
        if(PORTA == *port)
            SET_BIT(DDRA,pin);
        

        else if(PORTB == *port)
            SET_BIT(DDRB,pin);
            
        
        else if(PORTC == *port)
            SET_BIT(DDRC,pin);
            

        else if (PORTD == *port)    
            SET_BIT(DDRD,pin);
    }
    else if (io_mode == IN)
    {
        if(PORTA == *port)
            CLEAR_BIT(DDRA,pin);

        else if(PORTB == *port)
            CLEAR_BIT(DDRB,pin);
        
        else if(PORTC == *port)
            CLEAR_BIT(DDRC,pin);

        else if (PORTD == *port)    
            CLEAR_BIT(DDRD,pin);
    }    

}

/**
 * @brief define gpio_set_output()
 * 
 * @param pin 
 * @param port 
 * @param logic 
 */
void gpio_output_pin_value(volatile uint8_t pin,volatile uint8_t *port,volatile uint8_t logic)
{
    if (logic == VCC)
    {
        SET_BIT(*port,pin);
    }
    else if(logic == GND)
    {
        CLEAR_BIT(*port,pin);
    }
    else
    {
        // through error code
    }
}


/**
 * @brief define gpio_pullup_on()
 * 
 * @param pin 
 * @param port 
 */
void gpio_pullup_on(volatile uint8_t pin,volatile uint8_t *port)
{
    SET_BIT(*port,pin);
}


/**
 * @brief define gpio_pullup_off()
 * 
 * @param pin 
 * @param port 
 */
void gpio_pullup_off(volatile uint8_t pin,volatile uint8_t *port)
{
    CLEAR_BIT(*port,pin);
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
    CLEAR_BIT(SFIOR,PUD);
}


/**
 * @brief define gpio_read()
 * 
 * @param pin_number
 * @param pin 
 * 
 * @return uint8_t
 */
uint8_t gpio_read(volatile uint8_t pin_number,volatile uint8_t *pin)
{
    asm("nop");

    return (*pin & (1<<pin_number));
}