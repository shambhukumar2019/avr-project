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

#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include "common.h"




// external interrupts trigger logic level macros
/*

#define EI01_LOW_LEVEL      0U
#define EI0_ANY_LOGIC       1U
#define EI0_F_EDGE          2U
#define EI0_R_EDGE          3U
#define EI1_ANY_LOGIC       4U
#define EI1_F_EDGE          8U
#define EI1_R_EDGE          12U*/


// interrupt bits
#define    EXTERNAL_INTERRUPT_0                 INT0
#define    EXTERNAL_INTERRUPT_1                 INT1
//#define    EXTERNAL_INTERRUPT_2                 INT2
#define    T0_OVERFLOW_INTERRUPT                TOIE0
#define    T0_COMPARE_A_INTERRUPT               OCIE0A
#define    T0_COMPARE_B_INTERRUPT               OCIE0B
#define    T1_OVERFLOW_INTERRUPT                TOIE1
#define    T1_COMPARE_A_INTERRUPT               OCIE1A
#define    T1_COMPARE_B_INTERRUPT               OCIE1B
// #define    T1_CAPTURE_INTERRUPT                 TICIE1
// #define    T2_OVERFLOW_INTERRUPT                TOIE2
// #define    T2_COMPARE_INTERRUPT                 OCIE2
// #define    UART_RX_INTERRUPT                    RXCIE
// #define    UART_TX_INTERRUPT                    TXCIE
// #define    UART_UDRE_INTERRUPT                  UDRIE
#define    ADC_INTERRUPT                        ADIE
//#define    COMPARATOR_INTERRUPT                 ACIE
#define    SPI_INTERRUPT                        SPIE
//#define    I2C_INTERRUPT                        TWIE


// interrupt registers
#define TIMER0_INTERRUPT_REG                     TIMSK0
#define TIMER1_INTERRUPT_REG                     TIMSK1
//#define USART_INTERRUPT_REG                     UCSRB
#define EXT_INTERRUPT_REG                       EIMSK
#define ADC_INTERRUPT_REG                       ADCSRA
//#define COMPARATOR_INTERRUPT_REG                ACSR
#define SPI_CONTROL_REG                         SPCR
//#define I2C_INTERRUPT_REG                       TWCR

#define EXT_INT_LEVEL_CTRL_REG						EICRA



typedef enum
{
    LOW_LEVEL = 0,
	ANY_LOGIC_CHANGE,
	FALLING_EDGE,
    RISING_EDGE
}int_trig_level;


#define SET_INT_TRIG_LEVEL(int_trig_level)		{EXT_INT_LEVEL_CTRL_REG = int_trig_level;}





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


#define ENABLE_INTERRUPT(intr_reg,intr_bit)     SET_BIT(intr_reg,intr_bit)
#define DISABLE_INTERRUPT(intr_reg,intr_bit)    CLEAR_BIT(intr_reg,intr_bit)


extern volatile uint8_t tx_ds_flag;
extern volatile uint8_t rx_dr_flag;

//volatile uint8_t spi_isr_counter;


#endif