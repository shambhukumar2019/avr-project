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

#define USART_INTERRUPT_REG				UCSR0B
#define UART_FLAGS_REG					UCSR0A


#define ENABLE_UART_RX                  SET_BIT(USART_INTERRUPT_REG,RXEN0)
#define ENABLE_UART_TX                  SET_BIT(USART_INTERRUPT_REG,TXEN0)

#define ENABLE_UART_RX_INTERRUPT        ENABLE_INTERRUPT(USART_INTERRUPT_REG,RXCIE0)
#define ENABLE_UART_TX_INTERRUPT        ENABLE_INTERRUPT(USART_INTERRUPT_REG,TXCIE0)
#define ENABLE_UART_UDRE_INTERRUPT      ENABLE_INTERRUPT(USART_INTERRUPT_REG,UDRIE0)

#define DISABLE_UART_RX_INTERRUPT       DISABLE_INTERRUPT(USART_INTERRUPT_REG,RXCIE0)
#define DISABLE_UART_TX_INTERRUPT       DISABLE_INTERRUPT(USART_INTERRUPT_REG,TXCIE0)
#define DISABLE_UART_UDRE_INTERRUPT     DISABLE_INTERRUPT(USART_INTERRUPT_REG,UDRIE0)

#define UART_8BIT_FORMAT                (UCSR0C |= (3<<UCSZ00))

#define CLEAR_TXC_FLAG                  CLEAR_FLAG(UART_FLAGS_REG,TXC0)

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

void uart_send_string(volatile char* );

void uart_send_byte(uint8_t);

void uart_send_integer(uint32_t);

// uint8_t* uart_receive_string(void);

void string_copy(uint8_t* ,uint8_t* );

void clear_buffer(uint8_t* );

void integer_to_string(uint32_t , uint8_t* );

void string_to_integer(uint8_t*,uint16_t);

volatile uint8_t string_len(char*);
void reverse_string(char*);
void print_dectohex(uint32_t);

void uart_print(uint8_t *);

#endif