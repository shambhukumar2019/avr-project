/**
 * @file uart.h
 * @author shambhu kumar (you@domain.com)
 * @brief header file for uart device driver
 * @version 0.1
 * @date 2024-02-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _UART_H_
#define _UART_H_

#include "common.h"



#define BAUD_9600                       (9600UL)
#define BAUD_19200                      (19200UL)
#define BAUD_38400                      (38400UL)
#define BAUD_115200                     (115200UL)


#define UBRR_VALUE                      (uint8_t)((F_CPU / (16U * baud)) - 1U)



#define ENABLE_UART_RX                  SET_BIT(USART_INTERRUPT_REG,RXEN)
#define ENABLE_UART_TX                  SET_BIT(USART_INTERRUPT_REG,TXEN)

#define ENABLE_UART_RX_INTERRUPT        ENABLE_INTERRUPT(USART_INTERRUPT_REG,UART_RX_INTERRUPT)
#define ENABLE_UART_TX_INTERRUPT        ENABLE_INTERRUPT(USART_INTERRUPT_REG,UART_TX_INTERRUPT)
#define ENABLE_UART_UDRE_INTERRUPT      ENABLE_INTERRUPT(USART_INTERRUPT_REG,UART_UDRE_INTERRUPT)

#define DISABLE_UART_RX_INTERRUPT        DISABLE_INTERRUPT(USART_INTERRUPT_REG,UART_RX_INTERRUPT)
#define DISABLE_UART_TX_INTERRUPT        DISABLE_INTERRUPT(USART_INTERRUPT_REG,UART_TX_INTERRUPT)
#define DISABLE_UART_UDRE_INTERRUPT      DISABLE_INTERRUPT(USART_INTERRUPT_REG,UART_UDRE_INTERRUPT)

#define UART_8BIT_FORMAT                  (UCSRC |= (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0))

#define CLEAR_TXC_FLAG                  CLEAR_FLAG(UART_FLAGS_REG,UART_TXC_FLAG)


void uart_init(uint8_t);


#endif