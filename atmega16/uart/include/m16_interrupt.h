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

#define EI01_LOW_LEVEL      0U
#define EI0_ANY_LOGIC       1U
#define EI0_F_EDGE          2U
#define EI0_R_EDGE          3U
#define EI1_ANY_LOGIC       4U
#define EI1_F_EDGE          8U
#define EI1_R_EDGE          12U


// interrupt bits
#define    EXTERNAL_INTERRUPT_0                 INT0
#define    EXTERNAL_INTERRUPT_1                 INT1
#define    EXTERNAL_INTERRUPT_2                 INT2
#define    T0_OVERFLOW_INTERRUPT                TOIE0
#define    T0_COMPARE_INTERRUPT                 OCIE0
#define    T1_OVERFLOW_INTERRUPT                TOIE1
#define    T1_COMPARE_A_INTERRUPT               OCIE1A
#define    T1_COMPARE_B_INTERRUPT               OCIE1B
#define    T1_CAPTURE_INTERRUPT                 TICIE1
#define    T2_OVERFLOW_INTERRUPT                TOIE2
#define    T2_COMPARE_INTERRUPT                 OCIE2
#define    UART_RX_INTERRUPT                    RXCIE
#define    UART_TX_INTERRUPT                    TXCIE
#define    UART_UDRE_INTERRUPT                  UDRIE
#define    ADC_INTERRUPT                        ADIE
#define    COMPARATOR_INTERRUPT                 ACIE
#define    SPI_INTERRUPT                        SPIE
#define    I2C_INTERRUPT                        TWIE


// interrupt registers
#define TIMER_INTERRUPT_REG                     TIMSK
#define USART_INTERRUPT_REG                     UCSRB
#define EXT_INTERRUPT_REG                       GICR
#define ADC_INTERRUPT_REG                       ADCSRA
#define COMPARATOR_INTERRUPT_REG                ACSR
#define SPI_INTERRUPT_REG                       SPCR
#define I2C_INTERRUPT_REG                       TWCR



typedef enum trigger_mode
{
    NONE,
    LOW_LEVEL,
    RISING_EDGE,
    FALLING_EDGE,
    ANY_LOGIC_CHANGE
}trigger_mode;





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


#define CLEAR_FLAG(reg,bit)                     SET_BIT(reg,bit)




#endif