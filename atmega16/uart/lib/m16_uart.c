/**
 * @file m16_uart.c
 * @author shambhu kumar (you@domain.com)
 * @brief uart device driver source file
 * @version 0.1
 * @date 2024-02-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "m16_uart.h"


#define RX_ACTIVE       DISABLE
#define TX_ACTIVE       DISABLE
#define RX_TX_ACTIVE    ENABLE


void uart_init(uint8_t baud_rate)
{
    // SET_UART_BAUD_RATE(baud_rate);  // define a baud rate
    UBRRH = 0;
    UBRRL = 71;
    // set uart frame format to 8 bit data,
    // 1 start bit, 1 stop bit, no parity
    UART_8BIT_FORMAT;

    #if (RX_ACTIVE == ENABLE)
    {
        // wait until RXC flag clears that is rx buffer is empty
        while((UART_FLAGS_REG & (1<<UART_RXC_FLAG)) == 1);
        ENABLE_UART_RX;
    }
    #elif   (TX_ACTIVE == ENABLE)
    {
        // wait until TXC flag clear that is tx buffer and tx shift register is empty
        while((UART_FLAGS_REG & (1<<UART_TXC_FLAG)) == 1);
        ENABLE_UART_TX;
    }
    #elif   (RX_TX_ACTIVE == ENABLE)
    {
        
        ENABLE_UART_TX;
        ENABLE_UART_RX;
    }
    #endif

    
    ENABLE_UART_RX_INTERRUPT;
}