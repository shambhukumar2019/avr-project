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


void uart_init(void)
{
    uint8_t ubrr_value = 0;

    ubrr_value = UBRR_VALUE(BAUD_9600);
    UBRRH = ubrr_value >> 8;
    UBRRL = ubrr_value;
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

    // ENABLE_UART_UDRE_INTERRUPT;
    // ENABLE_UART_RX_INTERRUPT;
    CLEAR_TXC_FLAG;
}

/*uint8_t * uart_receive_string(void)
{
    if(uart.uart_rx_complete_flag == 1)
	{
		return uart.uart_buffer;
	}
	return NULL;
} */

void uart_send_string(uint8_t* send_string)
{
    clear_buffer(uart.uart_tx_buffer);
    string_copy(uart.uart_tx_buffer,send_string);
	ENABLE_UART_UDRE_INTERRUPT;
	DISABLE_UART_RX_INTERRUPT;
	_delay_ms(100);	// delay needed to tranfer string
}

void uart_send_byte(uint8_t byte)
{
    uint8_t character[2] = {0};

    character[0] = byte;

    uart_send_string(character);
}

void uart_send_integer(uint16_t decimal)
{
    uint8_t local_string[6] = {0};

    integer_to_string(decimal,local_string);

    uart_send_string(local_string);
}

void string_copy(uint8_t* dest,uint8_t* source)
{
	while(*source != '\0')
	{
		*dest = *source;
		dest++;
		source++;
	}
	*dest = '\0';
}

void clear_buffer(uint8_t* buffer)
{	
	while((*buffer) != '\0')
	{
		*buffer = 0;
		buffer++ ;
	}
	*buffer = 0;
}

void integer_to_string(uint16_t integer, uint8_t* string)
{
	uint8_t remainder = 0, index = 0, no_of_zeros = 0;
	uint16_t result = 0, dividend = 0;
	
	dividend = integer;
	
	
	while((dividend % 10) == 0)
	{
		if (integer == 0)
		{
			string[0] = 48;
			break;
		}
		dividend /= 10;
		no_of_zeros += 1;
	}
	while(integer != 0)
	{
		remainder = integer % 10;
		integer /= 10;
		result = result * 10 + remainder;
	}
	while(result != 0)
	{
		remainder = result % 10;
		result /= 10;
		string[index++] = remainder + 48;
	}
	for (result = 0;result < no_of_zeros;result++)
	{
		string[index + result] = 48;
	}
	index = 0;
}

void string_to_integer(uint8_t* string,uint16_t integer)
{
    
}

