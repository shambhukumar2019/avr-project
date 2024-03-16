#ifndef _MCP_3208_H_
#define _MCP_3208_H_

#include "common.h"

/**
 * @brief if using mcp3208 as adc with interrupt then enable this macro
 * 
 */
#define MCP3208_ADC_INTERRUPT       DISABLE

/**
 * @brief set reference voltage for mcp3208
 *          eg: 4.80v * 100 -> 480
 * 
 */
#define V_REF_MCP3208               480



#define ADC_MCP3208_CHANNEL_0       0
#define ADC_MCP3208_CHANNEL_1       1
#define ADC_MCP3208_CHANNEL_2       2
#define ADC_MCP3208_CHANNEL_3       3
#define ADC_MCP3208_CHANNEL_4       4
#define ADC_MCP3208_CHANNEL_5       5
#define ADC_MCP3208_CHANNEL_6       6
#define ADC_MCP3208_CHANNEL_7       7

//  store digital value from ADC
uint16_t adc_value_mcp3208;
uint8_t adc_high_byte,adc_low_byte;


void adc_init_mcp3208(void);

static void read_adc_mcp3208(uint8_t);

uint16_t read_millivolt_mcp3208(uint8_t);



uint16_t read_millivolt(uint8_t);

static void read_adc(uint8_t);








#endif
