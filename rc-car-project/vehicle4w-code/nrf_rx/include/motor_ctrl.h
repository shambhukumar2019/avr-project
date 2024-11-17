/*
 * motor_ctrl.h
 *
 * Created: 15-11-2024 14:44:44
 *  Author: ksham
 */ 


#ifndef MOTOR_CTRL_H_
#define MOTOR_CTRL_H_


#include "common.h"


#define MOTOR_PORT		PORTC
#define SERVO_PWM_PORT	PORTB
#define MOTOR_PWM_PORT	PORTD

#define MOTOR_DDR		DDRC
#define SERVO_PWM_DDR	DDRB
#define MOTOR_PWM_DDR	DDRD

#define MOTOR_PIN1		PORTC0
#define MOTOR_PIN2		PORTC1
#define SERVO_PWM_PIN	PORTB1
#define MOTOR_PWM_PIN	PORTD5


extern volatile uint8_t prev_servo_data, prev_motor_data, curr_servo_data, curr_motor_data, prev_front_back_data, curr_front_back_data;
extern uint8_t num;


void get_motor_ctrl_data(void);

void motor_init(void);

void dc_motor_ctrl(void);

void servo_motor_ctrl(void);

void ctrl_motor(void);


#endif /* MOTOR_CTRL_H_ */