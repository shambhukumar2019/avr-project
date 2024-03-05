/**
 * @file common.h
 * @author shambhu kumar (you@domain.com)
 * @brief header file containing all common declarations
 * @version 0.1
 * @date 2024-01-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _COMMON_H_
#define _COMMON_H_


#include "avr/io.h"
#include "m16_gpio.h"
#include "avr/interrupt.h"
#include "m16_interrupt.h"
#include "m16_uart.h"


#ifndef IOM_16_H
#define IOM_16_H

#include "avr/iom16.h"

#endif


#ifndef F_CPU
/**
 * @brief set clock frequency for CPU
 * 
 */
#define F_CPU 11059200UL
#endif


#define VCC         1U
#define GND         0U

#define ENABLE      VCC
#define TRUE        VCC
#define HIGH        VCC

#define DISABLE     GND
#define FALSE       GND
#define LOW         GND

#define SET_BIT(register,bit)       (register |= (1<<bit))
#define SET_BYTE(register)          (register = 0xFF)

#define CLEAR_BIT(register,bit)     (register &= ~(1<<bit))
#define CLEAR_BYTE(register)        (register = 0x00)

#define TOGGLE_BIT(register,bit)    (register ^= (1<<bit))

// extract high / low nibble from given register value
#define HIGH_NIBBLE(reg)            (reg & ((volatile uint8_t)0xF0))
#define LOW_NIBBLE(reg)             (reg & ((volatile uint8_t)0x0F))


volatile uint8_t value[3];


#endif
