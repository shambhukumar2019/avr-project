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
 * @param int_type 
 * @param int_mode 
 * @param trig_mode 
 * 
 * @attention "unused" attribute tells compiler that variable intentionally
 *            left unused so don't give warnings
 */
/* void config_interrupt(interrupt int_type,uint8_t int_mode,uint8_t trig_mode)
{
    switch (int_type)
    {
        case EXTERNAL_INTERRUPT_0:
        {
            if(int_mode == ENABLE)
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
            }
            else if (int_mode == DISABLE)
            {
                CLEAR_BIT(GICR,INT0);   // disable EXTERNAL_INTERRUPT_0
            }
        }break;

        case EXTERNAL_INTERRUPT_1:
        {
            if(int_mode == ENABLE)
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
            }
            else if(int_mode == DISABLE)
            {
                CLEAR_BIT(GICR,INT1);   // disable EXTERNAL_INTERRUPT_1
            }
        }break;

        case EXTERNAL_INTERRUPT_2:
        {
            if(int_mode == ENABLE)
            {
                CLEAR_BIT(GICR,INT2);   // disable EXTERNAL_INTERRUPT_2
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
                
                CLEAR_FLAG(GIFR,INTF2);
                SET_BIT(GICR,INT2); // enable external interrupt 2
            }
            else if (int_mode == DISABLE)
            {
                CLEAR_BIT(GICR,INT2);   // disable EXTERNAL_INTERRUPT_2
            }
        }break;

        case TIMER0_OVERFLOW_INTERRUPT:
        {
            if(int_mode == ENABLE)
            {
                SET_BIT(TIMSK,TOIE0);   // enable TIMER0_OVERFLOW_INTERRUPT
            }
            else if (int_mode == DISABLE)
            {
                CLEAR_BIT(TIMSK,TOIE0); // disable TIMER0_OVERFLOW_INTERRUPT
            }
        }break;

        case TIMER0_COMPARE_MATCH_INTERRUPT:
        {
            if(int_mode == ENABLE)
            {
                SET_BIT(TIMSK,OCIE0);   // enable TIMER0_COMPARE_MATCH_INTERRUPT
            }
            else if (int_mode == DISABLE)
            {
                CLEAR_BIT(TIMSK,OCIE0); // disable TIMER0_COMPARE_MATCH_INTERRUPT
            }
        }break;

        case TIMER1_OVERFLOW_INTERRUPT:
        {
            if(int_mode == ENABLE)
            {
                SET_BIT(TIMSK,TOIE1);   // enable TIMER1_OVERFLOW_INTERRUPT
            }
            else if (int_mode == DISABLE)
            {
                CLEAR_BIT(TIMSK,TOIE1); // disable TIMER1_OVERFLOW_INTERRUPT
            }
        }break;

        case TIMER1_COMPARE_MATCH_A_INTERRUPT:
        {
            if(int_mode == ENABLE)
            {
                SET_BIT(TIMSK,OCIE1A);   // enable TIMER1_COMPARE_MATCH_A_INTERRUPT
            }
            else if (int_mode == DISABLE)
            {
                CLEAR_BIT(TIMSK,OCIE1A); // disable TIMER1_COMPARE_MATCH_A_INTERRUPT
            }
        }break;

        case TIMER1_COMPARE_MATCH_B_INTERRUPT:
        {
            if(int_mode == ENABLE)
            {
                SET_BIT(TIMSK,OCIE1B);   // enable TIMER1_COMPARE_MATCH_B_INTERRUPT
            }
            else if (int_mode == DISABLE)
            {
                CLEAR_BIT(TIMSK,OCIE1B); // disable TIMER1_COMPARE_MATCH_B_INTERRUPT
            }
        }break;

        case TIMER1_INPUT_CAPTURE_INTERRUPT:
        {
            if(int_mode == ENABLE)
            {
                SET_BIT(TIMSK,TICIE1);   // enable TIMER1_INPUT_CAPTURE_INTERRUPT
            }
            else if (int_mode == DISABLE)
            {
                CLEAR_BIT(TIMSK,TICIE1); // disable TIMER1_INPUT_CAPTURE_INTERRUPT
            }
        }break;

        case TIMER2_OVERFLOW_INTERRUPT:
        {
            if(int_mode == ENABLE)
            {
                SET_BIT(TIMSK,TOIE2);   // enable TIMER2_OVERFLOW_INTERRUPT
            }
            else if (int_mode == DISABLE)
            {
                CLEAR_BIT(TIMSK,TOIE2); // disable TIMER2_OVERFLOW_INTERRUPT
            }
        }break;

        case TIMER2_COMPARE_MATCH_INTERRUPT:
        {
            if(int_mode == ENABLE)
            {
                SET_BIT(TIMSK,OCIE2);   // enable TIMER2_COMPARE_MATCH_INTERRUPT
            }
            else if (int_mode == DISABLE)
            {
                CLEAR_BIT(TIMSK,OCIE2); // disable TIMER2_COMPARE_MATCH_INTERRUPT
            }
        }break;

        case UART_RXC_INTERRUPT:
        {
            if(int_mode ==ENABLE)
            {
                SET_BIT(UCSRB,RXCIE);   // enable UART_RXC_INTERRUPT
            }
            else if (int_mode == DISABLE)
            {
                CLEAR_BIT(UCSRB,RXCIE); // disable UART_RXC_INTERRUPT
            }
        }break;

        case UART_TXC_INTERRUPT:
        {
            if(int_mode ==ENABLE)
            {
                SET_BIT(UCSRB,TXCIE);   // enable UART_TXC_INTERRUPT
            }
            else if (int_mode == DISABLE)
            {
                CLEAR_BIT(UCSRB,TXCIE); // disable UART_TXC_INTERRUPT
            }
        }break;

        case UART_UDRE_INTERRUPT:
        {
            if(int_mode ==ENABLE)
            {
                SET_BIT(UCSRB,UDRIE);   // enable UART_UDRE_INTERRUPT
            }
            else if (int_mode == DISABLE)
            {
                CLEAR_BIT(UCSRB,UDRIE); // disable UART_UDRE_INTERRUPT
            }
        }break;

        case ADC_INTERRUPT:
        {
            if(int_mode == ENABLE)
            {
                SET_BIT(ADCSRA,ADIE);   // enable ADC_INTERRUPT
            }
            else if (int_mode == DISABLE)
            {
                CLEAR_BIT(ADCSRA,ADIE); // disable ADC_INTERRUPT
            }
        }break;

        case COMPARATOR_INTERRUPT:
        {
            if(int_mode == ENABLE)
            {
                SET_BIT(ACSR,ACIE); // enable COMPARATOR_INTERRUPT
            }
            else if (int_mode == DISABLE)
            {
                CLEAR_BIT(ACSR,ACIE);   // disable COMPARATOR_INTERRUPT
            }
        }break;

        case SPI_INTERRUPT:
        {
            if(int_mode == ENABLE)
            {
                SET_BIT(SPCR,SPIE); // enable SPI_INTERRUPT
            }
            else if (int_mode == DISABLE)
            {
                CLEAR_BIT(SPCR,SPIE);   // disable SPI_INTERRUPT
            }
        }break;

        case I2C_INTERRUPT:
        {
            if(int_mode == ENABLE)
            {
                SET_BIT(TWCR,TWIE); // enable I2C_INTERRUPT
            }
            else if (int_mode == DISABLE)
            {
                CLEAR_BIT(TWCR,TWIE);   // disable I2C_INTERRUPT
            }
        }break;

        default:
        {
            // error code
        }break;
    }
} */


/**
 * @brief clear the flag of given interrupt
 * 
 * @param int_type 
 * 
 * @attention "unused" attribute tells compiler that variable intentionally
 *                  left unused so don't give warnings
 */
/*void clear_interrupt_flag(interrupt int_type)
{
    switch (int_type)
    {
        case EXTERNAL_INTERRUPT_0:
        {
            CLEAR_FLAG(GIFR,INTF0);  // clear EXTERNAL_INTERRUPT_0 flag
        }break;
        
        case EXTERNAL_INTERRUPT_1:
        {
            CLEAR_FLAG(GIFR,INTF1);  // clear EXTERNAL_INTERRUPT_1 flag
        }break;

        case EXTERNAL_INTERRUPT_2:
        {
            CLEAR_FLAG(GIFR,INTF2);  // clear EXTERNAL_INTERRUPT_2 flag
        }break;

        case TIMER0_OVERFLOW_INTERRUPT:
        {
            CLEAR_FLAG(TIFR,TOV0);   // clear TIMER0_OVERFLOW_INTERRUPT flag
        }break;

        case TIMER0_COMPARE_MATCH_INTERRUPT:
        {
            CLEAR_FLAG(TIFR,OCF0);   // clear TIMER0_COMPARE_MATCH_INTERRUPT flag
        }break;

        case TIMER1_OVERFLOW_INTERRUPT:
        {
            CLEAR_FLAG(TIFR,TOV1);   // clear TIMER1_OVERFLOW_INTERRUPT flag
        }break;

        case TIMER1_COMPARE_MATCH_A_INTERRUPT:
        {
            CLEAR_FLAG(TIFR,OCF1A);  // clear TIMER1_COMPARE_MATCH_A_INTERRUPT flag
        }break;

        case TIMER1_COMPARE_MATCH_B_INTERRUPT:
        {
            CLEAR_FLAG(TIFR,OCF1B);  // clear TIMER1_COMPARE_MATCH_B_INTERRUPT flag
        }break;

        case TIMER1_INPUT_CAPTURE_INTERRUPT:
        {
            CLEAR_FLAG(TIFR,ICF1);   // clear TIMER1_INPUT_CAPTURE_INTERRUPT flag
        }break;

        case TIMER2_OVERFLOW_INTERRUPT:
        {
            CLEAR_FLAG(TIFR,TOV2);   // clear TIMER2_OVERFLOW_INTERRUPT flag
        }break;

        case TIMER2_COMPARE_MATCH_INTERRUPT:
        {
            CLEAR_FLAG(TIFR,OCF2);   // clear TIMER2_COMPARE_MATCH_INTERRUPT flag
        }break;

        case UART_TXC_INTERRUPT:
        {
            CLEAR_FLAG(UCSRA,TXC);   // clear UART_TXC_INTERRUPT flag
        }break;

        case ADC_INTERRUPT:
        {
            CLEAR_FLAG(ADCSRA,ADIF); // clear ADC_INTERRUPT flag
        }break;

        case COMPARATOR_INTERRUPT:
        {
            CLEAR_FLAG(ACSR,ACI);    // clear COMPARATOR_INTERRUPT flag
        }break;

        case I2C_INTERRUPT:
        {
            CLEAR_FLAG(TWCR,TWINT);    // clear I2C_INTERRUPT flag
        }break;

        default:
        {
            // spi flag is cleared by 1st reading SPIF,
            // then accessing SPDR (SPI data register)
        }break;
    }
}
*/