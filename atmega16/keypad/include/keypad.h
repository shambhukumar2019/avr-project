/**
 * @file keypad.h
 * @author your name (you@domain.com)
 * @brief keypad driver header file
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _KEYPAD_H_
#define _KEYPAD_H_


#include "common.h"


#define R0      0
#define R1      1
#define R2      2
#define R3      3
#define C0      4
#define C1      5
#define C2      6
#define C3      7

#define KEYPAD_DDR      DDRC
#define KEYPAD_PORT     PORTC
#define KEYPAD_PIN      PINC


uint8_t keypad_lookup[4][4];



void keypad_init(void);

uint8_t keypad_scan(void);










#endif