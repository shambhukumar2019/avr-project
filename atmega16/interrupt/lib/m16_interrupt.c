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
 * 
 * @attention   SREG should be stored and restored on
 *              entering and exiting the ISR.
 * 
 * @attention   After ISR, cpu executes next instruction
 *              before any pending instruction
 * 
 * @attention   When an interrupt occurs, all interrupts are disabled.
 */
void config_interrupt(interrupt int_type,volatile uint8_t int_mode,volatile uint8_t trig_mode)
{
    #if (int_type == EXTERNAL_INTERRUPT_0)
    {
        if (LOW_LEVEL == trig_mode)
        {
            MCUCR = H_NIBBLE(MCUCR) | EI01_LOW_LEVEL;   // 00 -> low level trigger
        }
        else if (RISING_EDGE == trig_mode)
        {
            MCUCR = H_NIBBLE(MCUCR) | EI0_R_EDGE; // 11 -> rising edge
        }
        else if (FALLING_EDGE == trig_mode)
        {
            // 10 -> falling edge
            MCUCR = H_NIBBLE(MCUCR) | EI0_F_EDGE;
        }
        else if (ANY_LOGIC_CHANGE == trig_mode)
        {
            // 01 -> any logic change
            MCUCR = H_NIBBLE(MCUCR) | EI0_ANY_LOGIC;
        }
        else
        {
            // error code
        }

        SET_BIT(GICR,INT0); // enable EXTERNAL_INTERRUPT_0

        if (int_mode == DISABLE)
        {
            CLEAR_BIT(GICR,INT0);   // disable EXTERNAL_INTERRUPT_0
        }
        
    }
    #elif (int_type == EXTERNAL_INTERRUPT_1)
    {
        if (LOW_LEVEL == trig_mode)
        {
            MCUCR = H_NIBBLE(MCUCR) | EI01_LOW_LEVEL;   // 00 -> low level trigger
        }
        else if (RISING_EDGE == trig_mode)
        {
            MCUCR = H_NIBBLE(MCUCR) | EI1_R_EDGE; // 11 -> rising edge
        }
        else if (FALLING_EDGE == trig_mode)
        {
            // 10 -> falling edge
            MCUCR = H_NIBBLE(MCUCR) | EI1_F_EDGE;
        }
        else if (ANY_LOGIC_CHANGE == trig_mode)
        {
            // 01 -> any logic change
            MCUCR = H_NIBBLE(MCUCR) | EI1_ANY_LOGIC;
        }
        else
        {
            // error code
        }

        SET_BIT(GICR,INT1); // enable EXTERNAL_INTERRUPT_1

        if (int_mode == DISABLE)
        {
            CLEAR_BIT(GICR,INT1);   // disable EXTERNAL_INTERRUPT_1
        }
    }
    #elif (int_type == EXTERNAL_INTERRUPT_2)
    {
        // !! proper handling to be done !!
        if (trig_mode == FALLING_EDGE)
        {
            MCUCSR &= (~(1<<ISC2)); // 0 -> falling edge
        }
        else if (trig_mode == RISING_EDGE)
        {
            MCUCSR |= (1<<ISC2);    // 1 -> rising edge
        }
        else
        {
            // error code
        }
        
        SET_BIT(GICR,INT2); // enable external interrupt 2
    }
    #elif (int_type == TIMER0_OVERFLOW_INTERRUPT)
    {
        SET_BIT(TIMSK,TOIE0);   // enable TIMER0_OVERFLOW_INTERRUPT
        if (int_mode == DISABLE)
        {
            CLEAR_BIT(TIMSK,TOIE0); // disable TIMER0_OVERFLOW_INTERRUPT
        }
    }
    #elif (int_type == TIMER0_COMPARE_MATCH_INTERRUPT)
    {
        SET_BIT(TIMSK,OCIE0);   // enable TIMER0_COMPARE_MATCH_INTERRUPT
        if (int_mode == DISABLE)
        {
            CLEAR_BIT(TIMSK,OCIE0); // disable TIMER0_COMPARE_MATCH_INTERRUPT
        }
    }
    #elif (int_type == TIMER1_OVERFLOW_INTERRUPT)
    {
        SET_BIT(TIMSK,TOIE1);   // enable TIMER1_OVERFLOW_INTERRUPT
        if (int_mode == DISABLE)
        {
            CLEAR_BIT(TIMSK,TOIE1); // disable TIMER1_OVERFLOW_INTERRUPT
        }
    }
    #elif (int_type == TIMER1_COMPARE_MATCH_A_INTERRUPT)
    {
        SET_BIT(TIMSK,OCIE1A);  // enable TIMER1_COMPARE_MATCH_A_INTERRUPT
        if (int_mode == DISABLE)
        {
            CLEAR_BIT(TIMSK,OCIE1A);    // disable TIMER1_COMPARE_MATCH_A_INTERRUPT
        }
    }
    #elif (int_type == TIMER1_COMPARE_MATCH_B_INTERRUPT)
    {
        SET_BIT(TIMSK,OCIE1B);  // enable TIMER1_COMPARE_MATCH_B_INTERRUPT
        if (int_mode == DISABLE)
        {
            CLEAR_BIT(TIMSK,OCIE1B);    // disable TIMER1_COMPARE_MATCH_B_INTERRUPT
        }
    }
    #elif (int_type == TIMER1_INPUT_CAPTURE_INTERRUPT)
    {
        SET_BIT(TIMSK,TICIE1);  // enable TIMER1_INPUT_CAPTURE_INTERRUPT
        if (int_mode == DISABLE)
        {
            CLEAR_BIT(TIMSK,TICIE1);    // disable TIMER1_INPUT_CAPTURE_INTERRUPT
        }
    }
    #elif (int_type == TIMER2_OVERFLOW_INTERRUPT)
    {
        SET_BIT(TIMSK,TOIE2);   // enable TIMER2_OVERFLOW_INTERRUPT
        if (int_mode == DISABLE)
        {
            CLEAR_BIT(TIMSK,TOIE2); // disable TIMER2_OVERFLOW_INTERRUPT
        }
    }
    #elif (int_type == TIMER2_COMPARE_MATCH_INTERRUPT)
    {
        SET_BIT(TIMSK,OCIE2);   // enable TIMER2_COMPARE_MATCH_INTERRUPT
        if (int_mode == DISABLE)
        {
            CLEAR_BIT(TIMSK,OCIE2); // disable TIMER2_COMPARE_MATCH_INTERRUPT
        }
    }
    #elif (int_type == UART_RXC_INTERRUPT)
    {
        SET_BIT(UCSRA,RXCIE);   // enable UART_RXC_INTERRUPT
        if (int_mode == DISABLE)
        {
            CLEAR_BIT(UCSRB,RXCIE); // disable UART_RXC_INTERRUPT
        }
    }
    #elif (int_type == UART_TXC_INTERRUPT)
    {
        SET_BIT(UCSRA,TXCIE);   // enable UART_TXC_INTERRUPT
        if (int_mode == DISABLE)
        {
            CLEAR_BIT(UCSRB,TXCIE); // disable UART_TXC_INTERRUPT
        }
    }
    #elif (int_type == UART_UDRE_INTERRUPT)
    {
        SET_BIT(UCSRA,UDRIE);   // enable UART_UDRE_INTERRUPT
        if (int_mode == DISABLE)
        {
            CLEAR_BIT(UCSRB,UDRIE); // disable UART_UDRE_INTERRUPT
        }
    }
    #elif (int_type == ADC_INTERRUPT)
    {
        SET_BIT(ADCSRA,ADIE);   // enable ADC_INTERRUPT
        if (int_mode == DISABLE)
        {
            CLEAR_BIT(ADCSRA,ADIE); // disable ADC_INTERRUPT
        }
    }
    #elif (int_type == COMPARATOR_INTERRUPT)
    {
        SET_BIT(ACSR,ACIE); // enable COMPARATOR_INTERRUPT
        if (int_mode == DISABLE)
        {
            CLEAR_BIT(ACSR,ACIE);   // disable COMPARATOR_INTERRUPT
        }
    }
    #else
    {
        // error code
    }

    #endif
}


/**
 * @brief clear the flag of given interrupt
 * 
 * @param int_type type of interrupt from enum "interrupt_type" to clear its flag
 * 
 * @return void
 * 
 * @attention uart RXC and UDRE are read only flags, auto cleared by isr
 */
void clear_interrupt_flag(interrupt int_type)
{
    #if (int_type == EXTERNAL_INTERRUPT_0)
    {
        CLEAR_BIT(GIFR,INTF0);  // clear EXTERNAL_INTERRUPT_0 flag
    }
    #elif (int_type == EXTERNAL_INTERRUPT_1)
    {
        CLEAR_BIT(GIFR,INTF1);  // clear EXTERNAL_INTERRUPT_1 flag
    }
    #elif (int_type == EXTERNAL_INTERRUPT_2)
    {
        CLEAR_BIT(GIFR,INTF2);  // clear EXTERNAL_INTERRUPT_2 flag
    }
    #elif (int_type == TIMER0_OVERFLOW_INTERRUPT)
    {
        CLEAR_BIT(TIFR,TOV0);   // clear TIMER0_OVERFLOW_INTERRUPT flag
    }
    #elif (int_type == TIMER0_COMPARE_MATCH_INTERRUPT)
    {
        CLEAR_BIT(TIFR,OCF0);   // clear TIMER0_COMPARE_MATCH_INTERRUPT flag
    }
    #elif (int_type == TIMER1_OVERFLOW_INTERRUPT)
    {
        CLEAR_BIT(TIFR,TOV1);   // clear TIMER1_OVERFLOW_INTERRUPT flag
    }
    #elif (int_type == TIMER1_COMPARE_MATCH_INTERRUPT)
    {
        CLEAR_BIT(TIFR,OCF1A);  // clear TIMER1_COMPARE_MATCH_INTERRUPT flag
    }
    #elif (int_type == TIMER1_COMPARE_MATCH_INTERRUPT)
    {
        CLEAR_BIT(TIFR,OCF1B);  // clear TIMER1_COMPARE_MATCH_INTERRUPT flag
    }
    #elif (int_type == TIMER1_INPUT_CAPTURE_INTERRUPT)
    {
        CLEAR_BIT(TIFR,ICF1);   // clear TIMER1_INPUT_CAPTURE_INTERRUPT flag
    }
    #elif (int_type == TIMER2_OVERFLOW_INTERRUPT)
    {
        CLEAR_BIT(TIFR,TOV2);   // clear TIMER2_OVERFLOW_INTERRUPT flag
    }
    #elif (int_type == TIMER2_COMPARE_MATCH_INTERRUPT)
    {
        CLEAR_BIT(TIFR,OCF2);   // clear TIMER2_COMPARE_MATCH_INTERRUPT flag
    }
    #elif (int_type == UART_TXC_INTERRUPT)
    {
        CLEAR_BIT(UCSRA,TXC);   // clear UART_TXC_INTERRUPT flag
    }
    #elif (int_type == ADC_INTERRUPT)
    {
        CLEAR_BIT(ADCSRA,ADIF); // clear ADC_INTERRUPT flag
    }
    #elif (int_type == COMPARATOR_INTERRUPT)
    {
        CLEAR_BIT(ACSR,ACI);    // clear COMPARATOR_INTERRUPT flag
    }
    #else
    {
        // error code
    }
    #endif
}
