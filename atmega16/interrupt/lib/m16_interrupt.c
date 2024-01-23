/**
 * @file m16_interrupt.c
 * @author shambhu kumar (you@domain.com)
 * @brief function definitions of interrupt header file
 * @version 0.1
 * @date 2024-01-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "m16_interrupt.h"



/**
 * @brief configure given interrupt
 * 
 * @param int_type type of interrupt from enum "interrupt_type"
 * @param int_mode ENABLE or DISABLE the interrupt
 * @param trig_mode LEVEL, RISING_EDGE, FALLING_EDGE (only for external interrupts)
 * 
 * @return void
 */
void config_interrupt(interrupt_type int_type,volatile uint8_t int_mode,volatile uint8_t trig_mode)
{
    #if (int_type == EXTERNAL_INTERRUPT_0)
    {
        if (LOW_LEVEL == trig_mode)
        {
            MCUCR &= ((~(1<<ISC00)) & (~(1<<ISC01)));
        }
        else if (RISING_EDGE == trig_mode)
        {
            MCUCR |= ((1<<ISC00) | (1<<ISC01));
        }
        else if (FALLING_EDGE == trig_mode)
        {
            MCUCR &= (~(1<<ISC00));
            MCUCR |= (1<<ISC01);
        }
        else if (ANY_LOGIC_CHANGE == trig_mode)
        {
            MCUCR |= (1<<ISC00);
            MCUCR &= (~(1<<ISC01));
        }
        else
        {
            // error
        }

        SET_BIT(GICR,INT0); // enable external interrupt 0

        if (int_mode == DISABLE)
        {
            CLEAR_BIT(GICR,INT0);
        }
        
    }
    #elif (int_type == EXTERNAL_INTERRUPT_1)
    {
        if (LOW_LEVEL == trig_mode)
        {
            MCUCR &= ((~(1<<ISC00)) & (~(1<<ISC01)));
        }
        else if (RISING_EDGE == trig_mode)
        {
            MCUCR |= ((1<<ISC00) | (1<<ISC01));
        }
        else if (FALLING_EDGE == trig_mode)
        {
            MCUCR &= (~(1<<ISC10));
            MCUCR |= (1<<ISC11);
        }
        else if (ANY_LOGIC_CHANGE == trig_mode)
        {
            MCUCR |= (1<<ISC10);
            MCUCR &= (~(1<<ISC11));
        }
        else
        {
            // error
        }

        SET_BIT(GICR,INT1); // enable external interrupt 1

        if (int_mode == DISABLE)
        {
            CLEAR_BIT(GICR,INT1);
        }
    }
    #elif (int_type == EXTERNAL_INTERRUPT_2)
    {
        if (trig_mode == FALLING_EDGE)
        {
            MCUCSR &= (~(1<<ISC2));
        }
        else if (trig_mode == RISING_EDGE)
        {
            MCUCSR |= (1<<ISC2);
        }
        else
        {
            // error
        }
        
        SET_BIT(GICR,INT2); // enable external interrupt 2
    }
    #elif (int_type == TIMER0_OVERFLOW_INTERRUPT)
    {
        SET_BIT(TIMSK,TOIE0);
    }
    #elif (int_type == TIMER0_COMPARE_MATCH_INTERRUPT)
    {
        SET_BIT(TIMSK,OCIE0);
    }
    #elif (int_type == TIMER1_OVERFLOW_INTERRUPT)
    {
        SET_BIT(TIMSK,TOIE1);
    }
    #elif (int_type == TIMER1_COMPARE_MATCH_A_INTERRUPT)
    {
        SET_BIT(TIMSK,OCIE1A);
    }
    #elif (int_type == TIMER1_COMPARE_MATCH_B_INTERRUPT)
    {
        SET_BIT(TIMSK,OCIE1B);
    }
    #elif (int_type == TIMER1_INPUT_CAPTURE_INTERRUPT)
    {
        SET_BIT(TIMSK,TICIE1);
    }
    #elif (int_type == TIMER2_OVERFLOW_INTERRUPT)
    {
        SET_BIT(TIMSK,TOIE2);
    }
    #elif (int_type == TIMER2_COMPARE_MATCH_INTERRUPT)
    {
        SET_BIT(TIMSK,OCIE2);
    }
    #elif (int_type == UART_RXC_INTERRUPT)
    {
        SET_BIT(UCSRA,RXCIE);
    }
    #elif (int_type == UART_TXC_INTERRUPT)
    {
        SET_BIT(UCSRA,TXCIE);
    }
    #elif (int_type == UART_UDRE_INTERRUPT)
    {
        SET_BIT(UCSRA,UDRIE);
    }
    #elif (int_type == ADC_INTERRUPT)
    {
        SET_BIT(ADCSRA,ADIE);
    }
    #elif (int_type == COMPARATOR_INTERRUPT)
    {
        // statement
    }
    #else
    {
        // error
    }

    #endif
}


/**
 * @brief clear the flag of given interrupt
 * 
 * @param int_type type of interrupt from enum "interrupt_type" to clear its flag
 * 
 * @return void
 */
void clear_interrupt_flag(interrupt_type int_type)
{
    
}