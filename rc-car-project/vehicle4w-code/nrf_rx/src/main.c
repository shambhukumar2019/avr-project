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
	nrf_rx_init();
	motor_init();
	nrf_print_registers();
	
	SET_GLOBAL_INTERRUPT;
	
    for(;;) 
    {
		get_motor_ctrl_data();
		ctrl_motor();
    }
	
	return 0;
}

