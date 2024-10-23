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

    //ubrr_value = UBRR_VALUE(BAUD_9600);
    UBRR0H = 0;
    UBRR0L = 103;
    // set uart frame format to 8 bit data,
    // 1 start bit, 1 stop bit, no parity
    UART_8BIT_FORMAT;

   /* #if (RX_ACTIVE == ENABLE)
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
    {*/
        
        ENABLE_UART_TX;
        //ENABLE_UART_RX;
//     }
//     #endif

    CLEAR_TXC_FLAG;
}


void uart_send_string(volatile char* send_string)
{
//     clear_buffer(uart.uart_tx_buffer);
//     string_copy(uart.uart_tx_buffer,send_string);
	//ENABLE_UART_UDRE_INTERRUPT;
	//DISABLE_UART_RX_INTERRUPT;
	//_delay_ms(100);	// delay needed to tranfer string
	while(*send_string != '\0')
	{
		uart_send_byte(*send_string);
		send_string++;
	}
}

void uart_send_byte(uint8_t byte)
{
    /*uint8_t character[2] = {0};

    character[0] = byte;

    uart_send_string(character);*/
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = byte;
}

void uart_print(uint8_t *val)
{
	uart_send_string(val);
	uart_send_byte('\n');
}

void uart_send_integer(uint32_t decimal)
{
    uint8_t local_string[8] = {0};

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

void integer_to_string(uint32_t integer, uint8_t* string)
{
	uint8_t remainder = 0, index = 0, no_of_zeros = 0;
	uint32_t result = 0, dividend = 0;
	
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

void print_dectohex(uint32_t decimal)
{
	char hex_val[8] = {0};
	unsigned char index = 0;
	unsigned char rem = 0;
	unsigned long int dec_val = 0;

	dec_val = decimal;
	
	while(dec_val!=0)
	{
		rem = dec_val % 16;
		dec_val /= 16;
		
		if(rem < 10)
		{
			hex_val[index] = rem + 48;
		}
		else
		{
			hex_val[index] = (rem - 10) + 65;
		}

		index += 1;
	}//while end
	
	reverse_string(hex_val);
	uart_send_string(hex_val);
}

void reverse_string(char *src)
{
	unsigned char len = 0, l_index = 0;

	len = string_len(src);
	len -= 1;
	while(l_index < (len - l_index))
	{
		src[l_index] ^= src[len - l_index];
		src[len - l_index] ^= src[l_index];
		src[l_index] ^= src[len - l_index];

		l_index += 1;
	}
}

volatile uint8_t string_len(char *src)
{
	volatile uint8_t cnt = 0;
	while(*src != '\0')
	{
		cnt++;
		src++;
	}
	return cnt;
}

