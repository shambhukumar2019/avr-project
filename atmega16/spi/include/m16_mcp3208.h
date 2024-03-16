#ifndef _MCP_3208_H_
#define _MCP_3208_H_

#include "common.h"

// 4.8 v
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


void adc_init_mcp3208(void);

static void read_adc_mcp3208(uint8_t);

uint16_t read_millivolt_mcp3208(uint8_t);








#endif
