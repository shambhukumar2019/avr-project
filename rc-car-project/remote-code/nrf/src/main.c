/*
 * nrf.c
 *
 * Created: 27-09-2024 01:38:36
 * Author : ksham
 */ 

#include "common.h"



int main(void)
{
	volatile uint16_t adc_volt1 = 0;
	// let peripherals setup
	_delay_ms(100);
	
    spi_init(MASTER_MODE);
	uart_init();	// initiallize UART
	nrf_tx_init();
	nrf_print_registers();
	adc_init();
	adc_read(1);
	
	SET_GLOBAL_INTERRUPT;
	
    while (1) 
    {
		
		adc_volt1 = adc_read(1);	//servo motor, ADC1 channel
		
		uart_send_string("Servo PWM value: ");
		uart_send_integer(adc_volt1);
		
		nrf_tx_data(adc_volt1);
		adc_volt1 = adc_read(2);	//dc motor, ADC0 channel
		
		uart_send_string("DC Motor PWM value: ");
		uart_send_integer(adc_volt1);
		
		nrf_tx_data(adc_volt1);
		
		uart_send_string("DC Motor front move flag: ");
		nrf_tx_data(adc_front_move_flag + 48);
		uart_send_string(",    ");
		
		_delay_ms(1000);
    }
	
	return 0;
}

