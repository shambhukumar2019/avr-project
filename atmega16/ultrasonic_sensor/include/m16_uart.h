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


#define UBRR_VALUE(baud)                (uint8_t)((F_CPU / (16U * baud)) - 1U)



#define ENABLE_UART_RX                  SET_BIT(USART_INTERRUPT_REG,RXEN)
#define ENABLE_UART_TX                  SET_BIT(USART_INTERRUPT_REG,TXEN)

#define ENABLE_UART_RX_INTERRUPT        ENABLE_INTERRUPT(USART_INTERRUPT_REG,UART_RX_INTERRUPT)
#define ENABLE_UART_TX_INTERRUPT        ENABLE_INTERRUPT(USART_INTERRUPT_REG,UART_TX_INTERRUPT)
#define ENABLE_UART_UDRE_INTERRUPT      ENABLE_INTERRUPT(USART_INTERRUPT_REG,UART_UDRE_INTERRUPT)

#define DISABLE_UART_RX_INTERRUPT       DISABLE_INTERRUPT(USART_INTERRUPT_REG,UART_RX_INTERRUPT)
#define DISABLE_UART_TX_INTERRUPT       DISABLE_INTERRUPT(USART_INTERRUPT_REG,UART_TX_INTERRUPT)
#define DISABLE_UART_UDRE_INTERRUPT     DISABLE_INTERRUPT(USART_INTERRUPT_REG,UART_UDRE_INTERRUPT)

#define UART_8BIT_FORMAT                (UCSRC |= (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0))

#define CLEAR_TXC_FLAG                  CLEAR_FLAG(UART_FLAGS_REG,UART_TXC_FLAG)

#define UART_BUFFER_SIZE    100

typedef struct uart_memory
{
    uint8_t uart_rx_buffer[UART_BUFFER_SIZE + 1];
    uint8_t uart_tx_buffer[UART_BUFFER_SIZE + 1];
    uint8_t uart_buffer[UART_BUFFER_SIZE + 1];
    uint8_t uart_tx_index;
    uint8_t uart_rx_index;
    uint8_t uart_rx_complete_flag;

}uart_memory;
uart_memory uart;


void uart_init(void);

void uart_send_string(uint8_t* );

void uart_send_byte(uint8_t);

void uart_send_integer(uint32_t);

// uint8_t* uart_receive_string(void);

void string_copy(uint8_t* ,uint8_t* );

void clear_buffer(uint8_t* );

void integer_to_string(uint32_t , uint8_t* );

void string_to_integer(uint8_t*,uint16_t);


#endif