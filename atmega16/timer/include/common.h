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

#ifndef COMMON_H
#define COMMON_H



#ifndef F_CPU
/**
 * @brief set clock frequency for CPU
 * 
 */
#define F_CPU 11059200UL
#endif


#define VCC     1U
#define GND     0U
#define ENABLE      VCC
#define DISABLE     GND

#define SET_BIT(register,bit)       (register |= (1<<bit))
#define CLEAR_BIT(register,bit)     (register &= ~(1<<bit))
#define TOGGLE_BIT(register,bit)    (register ^= (1<<bit))

// extract high nibble from given register value

#define H_NIBBLE(reg)   (reg & ((volatile uint8_t)0xF0))

#endif