/**
 * @file m16_adc.h
 * @author shambbhu kumar (you@domain.com)
 * @brief adc device driver header file for atmega16/16A/32/32A
 * @version 0.1
 * @date 2024-03-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#ifndef ADC_H_
#define ADC_H_


#include "common.h"



/**
 * @brief reference voltage for adc
 * 
 */
#define ADC_V_REF           5000U

/**
 * @brief find step size in mV * 100
 * 
 */
#define ADC_STEP_SIZE       (uint16_t)((ADC_V_REF * 100UL) / 1024U)

// step size => Vref / 2^(adc bit size)


#define ADC_CHANNEL_0       0U
#define ADC_CHANNEL_1       1U
#define ADC_CHANNEL_2       2U
#define ADC_CHANNEL_3       3U
#define ADC_CHANNEL_4       4U
#define ADC_CHANNEL_5       5U
#define ADC_CHANNEL_6       6U
#define ADC_CHANNEL_7       7U

/**
 * @brief define ADC channel to select
 * 
 */
#define ADC_CHANNEL			        ADC_CHANNEL_0
#define SET_ADC_CHANNEL(chan)		ADMUX = ((ADMUX & 0xF0) | chan)


#define ADC_VREF_EXTERNAL           0x00U
#define ADC_VREF_AVCC               0x40U
#define ADC_VREF_INTERNAL           0xC0U

#define SET_ADC_VREF_POINT(vref)    (ADMUX |= (vref))



#define ADC_PRESCALAR_FACTOR_2      1U
#define ADC_PRESCALAR_FACTOR_4      2U
#define ADC_PRESCALAR_FACTOR_8      3U
#define ADC_PRESCALAR_FACTOR_16     4U
#define ADC_PRESCALAR_FACTOR_32     5U
#define ADC_PRESCALAR_FACTOR_64     6U
#define ADC_PRESCALAR_FACTOR_128    7U

/**
 * @brief set adc prescalar division factor
 * 
 */
#define SET_ADC_F_CPU_FACTOR(factor)    (ADCSRA |= (factor))



#define ENABLE_ADC			        SET_BIT(ADCSRA,ADEN)
#define DISABLE_ADC			        CLEAR_BIT(ADCSRA,ADEN)

#define ENABLE_ADC_INTERRUPT        SET_BIT(ADCSRA,ADIE)
#define DISABLE_ADC_INTERRUPT       CLEAR_BIT(ADCSRA,ADIE)

#define ADC_AUTO_TRIGGER_ENABLE     SET_BIT(ADCSRA,ADATE)
#define ADC_AUTO_TRIGGER_DISABLE    CLEAR_BIT(ADCSRA,ADATE)


//  ADC Auto Trigger Sources when ADC_AUTO_TRIGGER_ENABLE
#define ADC_ATS_COMPARATOR          0x20U
#define ADC_ATS_EI0                 0x40U
#define ADC_ATS_T0_COMPARE          0x60U
#define ADC_ATS_T0_OVERFLOW         0x80U
#define ADC_ATS_T1_COMPARE_B        0xA0U
#define ADC_ATS_T1_OVERFLOW         0xC0U
#define ADC_ATS_T1_CAPTURE          0xE0U

#define SET_ADC_ATS(source)         (SFIOR |= (source))



//in milli volts
#define MAX_VREF			    ADC_V_REF
#define MIN_VREF			    1000U
#define MAX_MIN_VREF_DIFF	    (MAX_VREF - MIN_VREF)   // 4v
#define MIN_VOLT_LIMIT		    ((MAX_MIN_VREF_DIFF / 20U) + MIN_VREF)          // 1.2v
#define MAX_VOLT_LIMIT		    ((MAX_MIN_VREF_DIFF / 5U) + MAX_MIN_VREF_DIFF)  // 4.8v

//10.81 => for 1ms, 10810 => 1s, timer1 compare match B
#define ADC_READ_PERIOD		    10810U

//give ADC voltage every 10s, maximum 255 seconds allowed
#define TIME_TO_GET_ADC_VOLT	1U

#define DEEP_DISCHARGE	        200U	//error code for deep discharge
#define OVER_CHARGE		        201U	//error code for over charge



volatile uint16_t millivolt_value,total_milli_volt;
volatile uint8_t time_in_second,adc_read_flag;
volatile uint32_t adc_digital_value;

extern uint8_t adc_front_move_flag;
extern uint8_t cnt;


void adc_init(void);

uint16_t adc_read(uint8_t);

void battery_status(void);

uint8_t adc_battery_percent(void);

//void print_volt(volatile uint16_t);

//uint16_t adc_decimal_to_float(volatile uint16_t, uint8_t*);

#endif /* ADC_H_ */