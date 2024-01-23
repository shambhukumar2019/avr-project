/**
 * @file m16_interrupt.h
 * @author shambhu kumar (you@domain.com)
 * @brief interrupt device driver header file
 * @version 0.1
 * @date 2024-01-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef M16_INTERRUPT_H
#define M16_INTERRUPT_H

#include "avr/io.h"

/**
 * @brief define clock frequency
 * 
 */
#define F_CPU   11059200UL


typedef enum
{
    EXTERNAL_INTERRUPT_0,
    EXTERNAL_INTERRUPT_1,
    EXTERNAL_INTERRUPT_2,
    TIMER0_OVERFLOW_INTERRUPT,
    TIMER0_COMPARE_MATCH_INTERRUPT,
    TIMER1_OVERFLOW_INTERRUPT,
    TIMER1_COMPARE_MATCH_A_INTERRUPT,
    TIMER1_COMPARE_MATCH_B_INTERRUPT,
    TIMER1_INPUT_CAPTURE_INTERRUPT,
    TIMER2_OVERFLOW_INTERRUPT,
    TIMER2_COMPARE_MATCH_INTERRUPT,
    UART_RXC_INTERRUPT,
    UART_TXC_INTERRUPT,
    UART_UDRE_INTERRUPT,
    ADC_INTERRUPT,
    COMPARATOR_INTERRUPT

}interrupt_type;


typedef enum
{
    LEVEL,
    RISING_EDGE,
    FALLING_EDGE
}trigger_mode;

#define ENABLE      1
#define DISABLE     0

#define SET_BIT(register,bit)       (register |= (1<<bit))
#define CLEAR_BIT(register,bit)     (register &= ~(1<<bit))

#define SET_GLOBAL_INTERRUPT        SET_BIT(SREG,SREG_I)
#define CLEAR_GLOBAL_INTERRUPT      CLEAR_BIT(SREG,SREG_I)


void config_interrupt(uint8_t,uint8_t,uint8_t);


void clear_interrupt_flag(uint8_t);


#endif