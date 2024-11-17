/*
 * motor_ctrl.c
 *
 * Created: 15-11-2024 14:44:59
 *  Author: ksham
 */ 

#include "motor_ctrl.h"


volatile uint8_t prev_servo_data = 0, prev_motor_data = 0, curr_servo_data = 0, curr_motor_data = 0, prev_front_back_data = 0, curr_front_back_data = 0;
uint8_t num = 1;


void get_motor_ctrl_data(void)
{
	volatile uint8_t byte = 0;
	
	byte = nrf_rx_data();
	if(byte != 0xFF)
	{
		if(num == 1)
		{
			uart_send_byte('#');
			curr_servo_data = byte;
			uart_send_integer(curr_servo_data);
			uart_send_byte('+');
			num = 2;
		}
		else if(num == 2)
		{
			num = 3;
			curr_motor_data = byte;
			
			uart_send_integer(curr_motor_data);
			uart_send_byte('+');
		}
		else if(num == 3)
		{
			num = 1;
			curr_front_back_data = byte;
			uart_send_integer(curr_front_back_data);
			uart_send_string("#  ");
		}
	}
}


void motor_init(void)
{
	// output pins
	MOTOR_DDR |= (1<<MOTOR_PIN1) | (1<<MOTOR_PIN2);
	MOTOR_PWM_DDR |= (1<<MOTOR_PWM_PIN);
	SERVO_PWM_DDR |= (1<<SERVO_PWM_PIN);
	
	// low logic on motor both pins
	MOTOR_PORT &= (~(1<<MOTOR_PIN1));
	MOTOR_PORT &= (~(1<<MOTOR_PIN2));
	
	// pin low
	SERVO_PWM_PORT &= ~(1<<SERVO_PWM_PIN);
	MOTOR_PWM_PORT &= ~(1<<MOTOR_PWM_PIN);
	
	//pwm_oc0b(0);	//dc motor, zero speed
	pwm_oc1a(150);	//servo motor, 0 degree
	
}

void dc_motor_ctrl(void)
{
	// control front and back movement of motor
	if(prev_front_back_data != curr_front_back_data)
	{
		if (curr_front_back_data == 1)
		{
			// front move
			MOTOR_PORT |= (1<<MOTOR_PIN1);
			MOTOR_PORT &= (~(1<<MOTOR_PIN2));
			//_delay_ms(2);
		}
		else if(curr_front_back_data == 0)
		{
			// back move
			MOTOR_PORT &= (~(1<<MOTOR_PIN1));
			MOTOR_PORT |= (1<<MOTOR_PIN2);
			//_delay_ms(2);
		}
		prev_front_back_data = curr_front_back_data;
	}
	
	
	// pwm on PD5 pin to control enable pin of L298n motor driver
	if(prev_motor_data != curr_motor_data)
	{
		pwm_oc0b(curr_motor_data);
		prev_motor_data = curr_motor_data;
	}
	
}

void servo_motor_ctrl(void)
{
	if(prev_servo_data != curr_servo_data)
	{
		pwm_oc1a(curr_servo_data);
		prev_servo_data = curr_servo_data;
	}
}

void ctrl_motor(void)
{
	dc_motor_ctrl();
	
	servo_motor_ctrl();
	
	
}