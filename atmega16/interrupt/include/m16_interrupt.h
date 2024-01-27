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
#include "m16_gpio.h"
#include "avr/interrupt.h"

#ifndef IOM_16_H
#define IOM_16_H

#include "avr/iom16.h"

#endif


#define H_NIBBLE(reg)   (reg & (volatile uint8_t)0xF0)


#define EI01_LOW_LEVEL      0U
#define EI0_ANY_LOGIC       1U
#define EI0_F_EDGE          2U
#define EI0_R_EDGE          3U
#define EI1_ANY_LOGIC       4U
#define EI1_F_EDGE          8U
#define EI1_R_EDGE          12U


typedef enum interrupt
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


typedef enum trigger_mode
{
    NONE,
    LOW_LEVEL,
    RISING_EDGE,
    FALLING_EDGE,
    ANY_LOGIC_CHANGE
}trigger_mode;


#define ENABLE      VCC
#define DISABLE     GND


/**
 * @attention instructions after this is executed
 *          before any pending interrupt
 * 
 */
#define SET_GLOBAL_INTERRUPT        SET_BIT(SREG,SREG_I)

/**
 * @attention no any pending interrupt executed 
 * 
 */
#define CLEAR_GLOBAL_INTERRUPT      sei()


#define CLEAR_FLAG(reg,bit)         cli()


void config_interrupt(interrupt,volatile uint8_t,volatile uint8_t);


void clear_interrupt_flag(interrupt);


#endif