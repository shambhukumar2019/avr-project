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

#include "common.h"
#include "avr/io.h"

#ifndef IOM_16_H
#define IOM_16_H

#include "avr/iom16.h"

#endif



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

}interrupt;


typedef enum
{
    NONE,
    LOW_LEVEL,
    RISING_EDGE,
    FALLING_EDGE,
    ANY_LOGIC_CHANGE
}trigger_mode;

#define ENABLE      VCC
#define DISABLE     GND


#define SET_GLOBAL_INTERRUPT        SET_BIT(SREG,SREG_I)
#define CLEAR_GLOBAL_INTERRUPT      CLEAR_BIT(SREG,SREG_I)


void config_interrupt(interrupt,volatile uint8_t,volatile uint8_t);


void clear_interrupt_flag(interrupt);


#endif