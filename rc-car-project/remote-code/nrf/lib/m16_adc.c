/**
 * @file m16_adc.c
 * @author shambbhu kumar (you@domain.com)
 * @brief adc device driver source code
 * @version 0.1
 * @date 2024-03-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "m16_adc.h"


volatile uint16_t total_milli_volt = 0;
volatile uint8_t adc_read_flag = 0;
volatile uint32_t adc_digital_value = 0;
uint8_t adc_front_move_flag = 0;

uint8_t cnt = 0;

/**
 * @brief intialize adc with given channel
 * 
 * @param channel select channel of adc to use from macros
 */
void adc_init(void)
{
	DIDR0 = 0x03;	// disable digital gpio on PC0(ADC0) and PC1(ADC0)
	ADMUX = 0;		// ADC channel 0 
	ENABLE_ADC;					// enable ADC
	SET_ADC_F_CPU_FACTOR(ADC_PRESCALAR_FACTOR_128);	// prescalar (Fosc / 128)
	SET_ADC_VREF_POINT(ADC_VREF_AVCC);				//AVCC as reference voltage
	ENABLE_ADC_INTERRUPT;							//ADC interrupt enable
	ADCSRA |= (1<<ADSC);
}


/**
 * @brief read in mV from selected channel
 * 
 * @return uint16_t milli volts value read
 */
uint16_t adc_read(uint8_t cnt)
{
	if (adc_read_flag == 1)
	{
		adc_read_flag = 0;
		//total_milli_volt = ((adc_digital_value * ADC_STEP_SIZE) / 100U);
		adc_digital_value /= 49;
		
		if(cnt == 1)
		{
			//uart_send_string("h2 ");
			SET_ADC_CHANNEL(0);
			// format it for servo motor pwm value to send over nrf
			adc_digital_value = 5 * adc_digital_value + 100;
		}
		else if(cnt == 2)
		{
			//uart_send_string("h3 ");
			SET_ADC_CHANNEL(1);
			
			//format for dc motor pwm to control speed
			if(adc_digital_value <= 10)
			{
				adc_front_move_flag = 0;
				adc_digital_value = 100 - (adc_digital_value * 10);
			}
			else if(adc_digital_value > 10)
			{
				adc_front_move_flag = 1;
				adc_digital_value = (adc_digital_value * 10) - 100;
			}
		}
		ADCSRA |= (1<<ADSC);	//start conversion
	}
	
	//ADC0 for dc Motor, ADC1 for servo motor
	return adc_digital_value;
}


/**
 * @brief show battery status and percentage
 * 
 */
void battery_status(void)
{
	volatile uint8_t bat_percent = 0;
	
	
	bat_percent = adc_battery_percent();
	if (bat_percent == OVER_CHARGE)
	{
		uart_send_string("\nOver charging\n");
	}
	else if (bat_percent == DEEP_DISCHARGE)
	{
		uart_send_string("\nDeep discharge\n");
	}
	else
	{
		uart_send_string("\nBattery => ");
		uart_send_integer(bat_percent);
		uart_send_string(" %");
	}
}


/**
 * @brief calculate battery percentage
 * 
 * @return uint8_t return battery percent
 */
uint8_t adc_battery_percent(void)
{
	if (millivolt_value < MIN_VOLT_LIMIT)
	{
		return DEEP_DISCHARGE;	
	}
	else if(millivolt_value > MAX_VOLT_LIMIT)
	{
		return OVER_CHARGE;	
	}
	else
	{
		return (((millivolt_value - MIN_VREF) * 100UL) / MAX_MIN_VREF_DIFF);
	}
}

/*
void print_volt(volatile uint16_t volt)
{
	uint8_t voltage[6] = {0};
	static uint8_t avg_count = 0;
	static uint16_t total_volt = 0;
	
	total_volt += volt;
	if (avg_count++ >= 30)
	{
		total_volt /= avg_count;
		adc_decimal_to_float(volt,voltage);
		uart_printf("Voltage: ");
		uart_printf((char*)voltage);
		uart_printf(" V\n");
		total_volt = 0;
		avg_count = 0;
	}
}*/

/*
uint16_t adc_decimal_to_float(volatile uint16_t volt_decimal, uint8_t* volt_string)
{
	uint8_t temp_volt_string[6] = {0};
		
	volt_decimal = (volt_decimal * 2.56 * 4.6875 * 100) / 1024;
	uart_decimal_to_string(volt_decimal,volt_string);

	if (volt_decimal <= 99)
	{
		temp_volt_string[0] = '0';
		temp_volt_string[1] = '.';
		temp_volt_string[2] = volt_string[0];
		temp_volt_string[3] = volt_string[1];
	}
	else if (volt_decimal <= 999)
	{
		temp_volt_string[0] = volt_string[0];
		temp_volt_string[1] = '.';
		temp_volt_string[2] = volt_string[1];
		temp_volt_string[3] = volt_string[2];
	} 
	else
	{
		temp_volt_string[0] = volt_string[0];
		temp_volt_string[1] = volt_string[1];
		temp_volt_string[2] = '.';
		temp_volt_string[3] = volt_string[2];
		temp_volt_string[4] = volt_string[3];
	}
	string_copy(volt_string,temp_volt_string);
	
	return (volt_decimal * 10);
}*/