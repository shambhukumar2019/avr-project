/**
 * @file m16_gpio.h
 * @author shambhu kumar (you@domain.com)
 * @brief atmega32 gpio header file for m32_gpio.c
 * @version 0.1
 * @date 2024-01-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef M32_GPIO_H
#define M32_GPIO_H

#include "common.h"
#include<avr/io.h>
#include "m16_interrupt.h"



/**
 * @brief   IN  -> make a pin as input
 */
#define IN          GND

/**
 * @brief OUT -> make a pin as output
 */
#define OUT         VCC


// PORTA pins alternate functions
#define ADC0_PIN                    PA0
#define ADC1_PIN                    PA1
#define ADC2_PIN                    PA2
#define ADC3_PIN                    PA3
#define ADC4_PIN                    PA4
#define ADC5_PIN                    PA5
#define ADC6_PIN                    PA6
#define ADC7_PIN                    PA7

// PORTB pins alternate functions
#define USART_EXT_CLK_IO_PIN        PB0
#define EXT_COUNTER_IN_0_PIN        PB0
#define EXT_COUNTER_IN_1_PIN        PB1
#define EXT_INTRRUPT_2_PIN          PB2
#define COMPARATOR_POS_IN_PIN       PB2
#define TIMER0_CMO_PIN              PB3
#define COMPARATOR_NEG_IN_PIN       PB3
#define SPI_SS_PIN                  PB4
#define SPI_MOSI_PIN                PB5
#define SPI_MISO_PIN                PB6
#define SPI_SCK_PIN                 PB7

// PORTC pins alternate functions
#define I2C_SCL_PIN                 PC0
#define I2C_SDA_PIN                 PC1
#define JTAG_TEST_CLK_PIN           PC2
#define JTAG_TEST_MODE_SEL_PIN      PC3
#define JTAG_TEST_DATA_OUT_PIN      PC4
#define JTAG_TEST_DATA_IN_PIN       PC5
#define TIMER_OSC_1_PIN             PC6
#define TIMER_OSC_2_PIN             PC7

// PORTD pins alternate functions
#define RXD_PIN                     PD0
#define TXD_PIN                     PD1
#define EXT_INTRRUPT_0_PIN          PD2
#define EXT_INTRRUPT_1_PIN          PD3
#define TIMER1_CMO_B_PIN            PD4
#define TIMER1_CMO_A_PIN            PD5    
#define TIMER1_IC_PIN               PD6
#define TIMER2_CMO_PIN              PD7


#define GPIO_OUTPUT_HIGH(port,pin)      SET_BIT(port,pin)           
#define GPIO_OUTPUT_LOW(port,pin)       SET_BIT(port,pin)

/*  compiler treat it as integer,
    default pinvalue size = 4 byte

    but if we use "packed" attribute
    then pinvalue will use least size needed.
    __attribute__ ((__packed__))
*/


/**
 * @brief set given pin of a port as output
 * 
 * @param uint8_t store pin number
 * @param uint8_t store port address
 * @param uint8_t set i/o mode (IN/OUT)
 * 
 * @return void
 */
void gpio_pin_mode(volatile uint8_t,volatile uint8_t *,volatile uint8_t);




/**
 * @brief turn on pull-up for given pin of the port
 * 
 * @param uint8_t store pin number
 * @param uint8_t store port address
 * 
 * @return void
 */
void gpio_pullup_on(volatile uint8_t,volatile uint8_t *);


/**
 * @brief turn off pull-up for given pin of the port
 * 
 * @param uint8_t store pin number
 * @param uint8_t store port address
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
 * @param uint8_t set the pin address
 * 
 * @return volatile uint8_t  pin value (VCC/GND)
 */
uint8_t gpio_read(volatile uint8_t,volatile uint8_t *);





#endif