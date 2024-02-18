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



// peripheral flags macros

#define EI0_FLAG                        INTF0
#define EI1_FLAG                        INTF1
#define EI2_FLAG                        INTF2
#define T0_OVERFLOW_FLAG                TOV0
#define T0_COMPARE_FLAG                 OCF0
#define T1_OVERFLOW_FLAG                TOV1
#define T1_COMPARE_A_FLAG               OCF1A
#define T1_COMPARE_B_FLAG               OCF1B
#define T1_INPUT_CAPTURE_FLAG           ICF1
#define T2_OVERFLOW_FLAG                TOV2
#define T2_COMPARE_FLAG                 OCF2
#define UART_TCX_FLAG                   TXC
#define ADC_FLAG                        ADIF
#define COMPARATOR_FLAG                 ACI
#define I2C_FLAG                        TWINT



// peripherals flag registers macros

#define EI_FLAGS_REG                    GIFR
#define TIMER_FLAGS_REG                 TIFR
#define UART_FLAGS_REG                  UCSRA
#define ADC_FLAGS_REG                   ADCSRA
#define COMPARATOR_FLAGS_REG            ACSR
#define I2C_FLAGS_REG                   TWCR


// extract high nibble from given register value

#define H_NIBBLE(reg)   (reg & ((volatile uint8_t)0xF0))



// external interrupts trigger logic level macros

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
    COMPARATOR_INTERRUPT,
    SPI_INTERRUPT,
    I2C_INTERRUPT
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
#define SET_GLOBAL_INTERRUPT        sei()

/**
 * @attention no any pending interrupt executed 
 * 
 */
#define CLEAR_GLOBAL_INTERRUPT      cli()


#define CLEAR_FLAG(reg,bit)         SET_BIT(reg,bit)


/**
 * @brief configure given interrupt
 * 
 * @param interrupt type of interrupt from enum "interrupt_type"
 * @param uint8_t ENABLE or DISABLE the interrupt
 * @param uint8_t LEVEL, RISING_EDGE, FALLING_EDGE (only for external interrupts)
 * 
 * @return void
 * 
 * 
 * @attention   SREG should be stored and restored on
 *              entering and exiting the ISR.
 * 
 * @attention   After ISR, cpu executes next instruction
 *              before any pending instruction
 * 
 * @attention   When an interrupt occurs, all interrupts are disabled.
 */
void config_interrupt(interrupt,uint8_t,uint8_t);



/**
 * @brief clear the flag of given interrupt
 * 
 * @param interrupt type of interrupt from enum "interrupt_type" to clear its flag
 * 
 * @return void
 * 
 * @attention uart RXC and UDRE are read only flags, auto cleared by isr
 */
// void clear_interrupt_flag(interrupt);


#endif