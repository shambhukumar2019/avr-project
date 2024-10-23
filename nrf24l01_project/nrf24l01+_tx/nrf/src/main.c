/*
 * nrf.c
 *
 * Created: 27-09-2024 01:38:36
 * Author : ksham
 */ 

#include "common.h"


int main(void)
{
	// let peripherals setup
	_delay_ms(100);
	
    spi_init(MASTER_MODE);
	uart_init();
	nrf_tx_init();
	nrf_print_registers();
	
    while (1) 
    {
		nrf_transmit_string("This is Shambhu kumar. ");
		_delay_ms(5000);
		
    }
	
	return 0;
}

