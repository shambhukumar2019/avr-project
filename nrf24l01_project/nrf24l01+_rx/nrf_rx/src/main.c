/*
 * nrf.c
 *
 * Created: 27-09-2024 01:38:36
 * Author : ksham
 */ 

#include "common.h"


int main(void)
{
	volatile uint8_t byte = 0;
	
	// let peripherals setup
	_delay_ms(100);
	
    spi_init(MASTER_MODE);
	uart_init();
	nrf_rx_init();
	nrf_print_registers();
	
    while (1) 
    {
		byte = nrf_rx_data();
		uart_send_byte(byte);
    }
	
	return 0;
}

