/**
 * @file m16_timer.h
 * @author shambhu kumar (you@domain.com)
 * @brief timer device driver header file
 * @version 0.1
 * @date 2024-03-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#ifndef _TIMER_H_
#define _TIMER_H_

#include "common.h"

/*

#define ENABLE_ICP_FALL_EDGE    {   TCCR1A = 0U;\
                                    TCCR1B = 0x81;\
                                }

#define ENABLE_ICP_RISE_EDGE    {   TCCR1A = 0U;\
                                    TCCR1B = 0xC1;\
                                }

#define DISABLE_ICP             {   TCCR1A = 0U;\
                                    TCCR1B = 0U;\
                                }*/


/*

typedef enum pwm_pin{
    OC0_PIN,
    OC1A_PIN,
    OC1B_PIN,
    OC2_PIN
}pwm_pin;

typedef enum pwm_freq{
    FREQ_100,
    FREQ_200,
    FREQ_300,
    FREQ_400,
    FREQ_500,
    FREQ_600,
    FREQ_675,
    FREQ_700,
    FREQ_800,
    FREQ_900,
    FREQ_1000,
    FREQ_1350,
    FREQ_5400,
    FREQ_43200,
}pwm_freq;
*/


/// @brief polled delay in milliseconds
/// @param  value in milliseconds
void ms_delay(uint16_t);



/// @brief polled delay in microseconds
/// @param  value in microseconds
void us_delay(uint16_t);


/*




void pwm_oc2(pwm_freq ,uint8_t);

void pwm_oc1a(pwm_freq ,uint8_t);
*/
void pwm_oc0b(volatile uint8_t);

// 105 -> 9 degree, 110 -> 18 degree
void pwm_oc1a(volatile uint8_t);



/// @brief configure any timer in any mode for a given time using interrupt
/// @param  timer
/// @param  mode of timer
/// @param  delay value
void config_timer(uint8_t,uint8_t,uint16_t);



/// @brief measure input signal frequency on ICP pin
/// @param  void
/// @return measured frequency in kHz
uint16_t measure_frequency(void);



/// @brief measure input signal duty cycle on ICP pin
/// @param  void
/// @return measured dutycycle in percentage
uint8_t measure_dutycycle(void);






#endif