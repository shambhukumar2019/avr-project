#include "m32_gpio.h"


void gpio_setout(uint8_t pin,uint8_t port)
{
    if(PORTA == port)
        
        DDRA |= (1<<pin);

    else if(PORTB == port)

        DDRB |= (1<<pin);
    
    else if(PORTC == port)

        DDRC |= (1<<pin);

    else if (PORTD == port)    

        DDRD |= (1<<pin);

}

void gpio_setin(uint8_t pin,uint8_t port)
{
    if(PORTA == port)
        
        DDRA &= ~(1<<pin);

    else if(PORTB == port)

        DDRB &= ~(1<<pin);
    
    else if(PORTC == port)

        DDRC &= ~(1<<pin);

    else if (PORTD == port)    

        DDRD &= ~(1<<pin);
}

void gpio_set_output(uint8_t pin,uint8_t port,uint8_t logic)
{
    if(PORTA == port)
    {
        if (logic == VCC)
        {
            PORTA |= (1<<pin);
        }
        else if(logic == GND)
        {
            PORTA &= ~(1<<pin);
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
            PORTB |= (1<<pin);
        }
        else if(logic == GND)
        {
            PORTB &= ~(1<<pin);
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
            PORTC |= (1<<pin);
        }
        else if(logic == GND)
        {
            PORTC &= ~(1<<pin);
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
            PORTD |= (1<<pin);
        }
        else if(logic == GND)
        {
            PORTD &= ~(1<<pin);
        }
        else
        {
            // through error code
        }
    }
}

void gpio_pullup_on(uint8_t pin,uint8_t port)
{
    if(PORTA == port)
        
        PORTA |= (1<<pin);

    else if(PORTB == port)

        PORTB |= (1<<pin);
    
    else if(PORTC == port)

        PORTC |= (1<<pin);

    else if (PORTD == port)    

        PORTD |= (1<<pin);
}

void gpio_pullup_off(uint8_t pin,uint8_t port)
{
    if(PORTA == port)
        
        PORTA &= ~(1<<pin);

    else if(PORTB == port)

        PORTB &= ~(1<<pin);
    
    else if(PORTC == port)

        PORTC &= ~(1<<pin);

    else if (PORTD == port)    

        PORTD &= ~(1<<pin);
}


void gpio_pullup_disable(void)
{
    SFIOR |= (1 << PUD);
}


void gpio_pullup_enable(void)
{
    SFIOR &= ~(1 << PUD);
}


volatile uint8_t gpio_read(uint8_t pin,uint8_t port)
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