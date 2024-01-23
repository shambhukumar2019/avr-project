/**
 * @file m32_gpio.h
 * @author shambhu kumar (you@domain.com)
 * @brief atmega32 gpio header file for m32_gpio.c
 * @version 1.0
 * @date 2024-01-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef M32_GPIO_H
#define M32_GPIO_H

#include<avr/io.h>
//#include<avr/iom32.h>

#ifndef F_CPU
/**
 * @brief set clock frequency for CPU
 * 
 */
#define F_CPU 11059200UL
#endif


#define VCC         1
#define GND         0

/**
 * @brief   IN  -> make a pin as input
 */
#define IN          GND

/**
 * @brief OUT -> make a pin as output
 */
#define OUT         VCC


/*
typedef unsigned char pin;      // to store pin number
typedef unsigned char port;     // to store port name
typedef unsigned char logic;    // to store logic level (VCC/GND)
*/



/*  compiler treat it as integer,
    default pinvalue size = 4 byte

    but if we use "packed" attribute
    then pinvalue will use least size needed.
    __attribute__ ((__packed__))
*/
/*
typedef enum
{
    pin1,
    pin2,
    pin3,
    pin4,
    pin5,
    pin6,
    pin7,
    pin8
}pinvalue;
*/



/*
    store variables for pin number,
    port number and logic level set.

    to minimize space required bitfields are used.

    only 2 byte space will be occupied.

    further thinking required...
*/
/*
typedef struct
{
    uint8_t port    :8;
    uint8_t pin     :4;
    uint8_t logic   :1;
}gpio_config;
*/


/**
 * @brief set given pin of a port as output
 * 
 * @param uint8_t store pin number
 * @param uint8_t store port name
 * @param uint8_t set i/o mode (IN/OUT)
 * 
 * @return void
 */
void gpio_pin_mode(volatile uint8_t,volatile uint8_t *,volatile uint8_t);


/**
 * @brief set value for pin (high/low) of the port
 * 
 * @param uint8_t store pin number
 * @param uint8_t store port name
 * @param uint8_t set pin value (VCC/GND)
 * 
 * @return void
 */
void gpio_set_output_pin_value(volatile uint8_t,volatile uint8_t*,volatile uint8_t);


/**
 * @brief turn on pull-up for given pin of the port
 * 
 * @param uint8_t store pin number
 * @param uint8_t store port name
 * 
 * @return void
 */
void gpio_pullup_on(volatile uint8_t,volatile uint8_t *);


/**
 * @brief turn off pull-up for given pin of the port
 * 
 * @param uint8_t store pin number
 * @param uint8_t store port name
 * 
 * @return void
 */
void gpio_pullup_off(volatile uint8_t,volatile uint8_t *);


/**
 * @brief disable pull-up for all ports
 * 
 * @param void
 * 
 * @return void
 */
void gpio_global_pullup_disable(void);


/**
 * @brief enable pull-up for all ports
 * 
 * @param void
 * 
 * @return void
 */
void gpio_global_pullup_enable(void);


/**
 * @brief read value of the pin of the port
 * 
 * @param uint8_t set the pin number
 * @param uint8_t set the port name
 * 
 * @return volatile uint8_t  pin value (VCC/GND)
 */
uint8_t gpio_read(volatile uint8_t,volatile uint8_t *);





#endif