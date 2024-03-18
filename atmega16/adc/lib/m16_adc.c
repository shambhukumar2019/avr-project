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


volatile uint16_t millivolt_value = 0,total_milli_volt = 0;
volatile uint8_t time_in_second = 0,adc_read_flag = 0;
volatile uint32_t adc_digital_value = 0;


/**
 * @brief intialize adc with given channel
 * 
 * @param channel select channel of adc to use from macros
 */
void adc_init(uint8_t channel)
{
	ADMUX = channel;		// ADC channel 0 
	ENABLE_ADC;					// enable ADC
	SET_ADC_F_CPU_FACTOR(ADC_PRESCALAR_FACTOR_128);	// prescalar (Fosc / 128)
	SET_ADC_VREF_POINT(ADC_VREF_AVCC);				//AVCC as reference voltage
	ENABLE_ADC_INTERRUPT;							//ADC interrupt enable
	ADC_AUTO_TRIGGER_ENABLE;						//auto trigger enable
	SET_ADC_ATS(ADC_ATS_T1_COMPARE_B);				//OCR1B as source of auto trigger

	// timer initialization for auto trigger on output compare match
	OCR1B = ADC_READ_PERIOD;	// exactly 10.8 => for 1 ms,
	TCNT1 = 0;					//initial counter value 0
	TCCR1A = 0;
	TCCR1B = 0x0D;				//compare match mode with prescalar (Fosc / 1024)
}


/**
 * @brief read in mV from selecterd channel
 * 
 * @return uint16_t milli volts value read
 */
uint16_t adc_read(void)
{
	//print_decimal(ADCW);
	if (adc_read_flag == 1)
	{
		adc_read_flag = 0;
		adc_digital_value = ((adc_digital_value * ADC_STEP_SIZE) / 100U);
		total_milli_volt += (uint16_t)adc_digital_value;
		time_in_second += 1;
		
		if (time_in_second >= TIME_TO_GET_ADC_VOLT)
		{
			total_milli_volt /= time_in_second;
			millivolt_value = total_milli_volt;	//get average of value by time_in_second
			total_milli_volt = 0;
			time_in_second = 0;
			//adc_ready_flag = 1;	//set to let user use the value
			return millivolt_value;
		}
	}
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