/**
 * @file ultrasonic_sensor.h
 * @author your name (you@domain.com)
 * @brief header file
 * @version 0.1
 * @date 2024-04-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _ULTRASONIC_SENSOR_H_
#define _ULTRASONIC_SENSOR_H_


#include "common.h"


#define TRIG_PORT   PORTD
#define TRIG_PIN    PD7

#define ECHO_PORT   PORTD
#define ECHO_PIN    T1_ICP_PIN


#define SEND_TRIGGER_PULSE          {   GPIO_PIN_HIGH(TRIG_PORT,TRIG_PIN);\
                                        _delay_us(20);\
                                        GPIO_PIN_LOW(TRIG_PORT,TRIG_PIN);\
                                    }









#endif