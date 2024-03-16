/**
 * @file m16_isr.c
 * @author shambhu kumar (you@domain.com)
 * @brief define all ISR(interrupt sub-routines) in this file
 * @version 0.1
 * @date 2024-01-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "m16_interrupt.h"
// #include "m16_uart.h"



ISR(SPI_STC_vect)
{
    spdr_rx_byte = SPDR;
}

ISR(INT0_vect)
{
    // GPIO_OUTPUT_HIGH(PORTA,PA0);
}

ISR(TIMER0_OVF_vect)
{
    /* count++;
    if(count >= 50)
    {
        count = 0;
        GPIO_PIN_TOGGLE(PORTA,PIN0);
    }
    TCNT0 = 0x00; */
    // GPIO_PIN_TOGGLE(PORTA,PIN0);
    // TCNT0 = 250;
}

ISR(TIMER0_COMP_vect)
{
    //OCR0 = 250;
}

ISR(TIMER1_COMPA_vect)
{
      
    
}

ISR(TIMER1_CAPT_vect)
{
    /* f1 = ICR1;
    if (count == 0)
    {
        f2 = f1;
        count++;
    }
    else
    {
        count = 0;
        f2 = f1 - f2;
        TIMSK &= ~(1<<TICIE1);
    } */
}

ISR(USART_UDRE_vect)
{
   UDR = uart.uart_tx_buffer[uart.uart_tx_index++];
   if (uart.uart_tx_buffer[uart.uart_tx_index] == '\0')
   {
        DISABLE_UART_UDRE_INTERRUPT;
        uart.uart_tx_index = 0;
        ENABLE_UART_RX_INTERRUPT;
   }
   
}

ISR(USART_RXC_vect)
{
    uart.uart_rx_buffer[uart.uart_rx_index] = UDR;
    uart.uart_rx_index++;
    if(uart.uart_rx_buffer[uart.uart_rx_index - 1] == '\n')
    {
        uart.uart_rx_buffer[uart.uart_rx_index - 1] = '\n';
        uart.uart_rx_buffer[uart.uart_rx_index] = '\0';
        string_copy(uart.uart_buffer,uart.uart_rx_buffer);
        uart.uart_rx_index = 0;
        uart.uart_rx_complete_flag = 1;
    }
}

ISR(BADISR_vect)
{
    
}


