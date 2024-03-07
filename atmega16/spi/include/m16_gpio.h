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
#ifndef _GPIO_H_
#define _GPIO_H_


#include "common.h"



/**
 * @brief   IN  -> make a pin as input
 */
#define INPUT          GND

/**
 * @brief OUT -> make a pin as output
 */
#define OUTPUT         VCC


#define GPIO_GLOBAL_PULLUP_ENABLE   CLEAR_BIT(SFIOR,PUD)
#define GPIO_GLOBAL_PULLUP_DISABLE  SET_BIT(SFIOR,PUD)

#define GPIO_PULLUP_ON(port,pin)    SET_BIT(port,pin)
#define GPIO_PULLUP_OFF(port,pin)   CLEAR_BIT(port,pin)


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
#define EXT_T0_PIN                  PB0
#define EXT_T1_PIN                  PB1
#define EXT_INTRRUPT_2_PIN          PB2
#define COMPARATOR_POS_IN_PIN       PB2
#define TIMER0_OC_PIN               PB3
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
#define TIMER1_OC_B_PIN             PD4
#define TIMER1_OC_A_PIN             PD5    
#define TIMER1_ICP_PIN              PD6
#define TIMER2_OC_PIN               PD7



// peripheral flags macros

#define EI0_FLAG                        INTF0
#define EI1_FLAG                        INTF1
#define EI2_FLAG                        INTF2
#define T0_OVERFLOW_FLAG                TOV0
#define T0_COMPARE_FLAG                 OCF0
#define T1_OVERFLOW_FLAG                TOV1
#define T1_COMPARE_A_FLAG               OCF1A
#define T1_COMPARE_B_FLAG               OCF1B
#define T1_INPUT_CAPTURE_FLAG           ICF1
#define T2_OVERFLOW_FLAG                TOV2
#define T2_COMPARE_FLAG                 OCF2
#define UART_TXC_FLAG                   TXC
#define UART_RXC_FLAG                   RXC
#define UART_UDRE_FLAG                  UDRE
#define ADC_FLAG                        ADIF
#define COMPARATOR_FLAG                 ACI
#define I2C_FLAG                        TWINT



// peripherals flag registers macros

#define EI_FLAGS_REG                    GIFR
#define TIMER_FLAGS_REG                 TIFR
#define UART_FLAGS_REG                  UCSRA
#define ADC_FLAGS_REG                   ADCSRA
#define COMPARATOR_FLAGS_REG            ACSR
#define I2C_FLAGS_REG                   TWCR
#define SPI_FLAGS_REG                   SPSR


/**
 * @brief set an output pin high for given port
 * 
 */
#define GPIO_PIN_HIGH(port,pin)         SET_BIT(port,pin) 

/**
 * @brief set an output pin low for given port
 * 
 */
#define GPIO_PIN_LOW(port,pin)          CLEAR_BIT(port,pin)

/**
 * @brief toggle output pin for given port
 * 
 */
#define GPIO_PIN_TOGGLE(port,pin)       TOGGLE_BIT(port,pin)




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
void gpio_pin_mode(uint8_t,volatile uint8_t *,uint8_t);


void gpio_port_mode(volatile uint8_t *,uint8_t);



/**
 * @brief read value of the pin of the port
 * 
 * @param uint8_t set the pin number
 * @param uint8_t set the pin address
 * 
 * @return volatile uint8_t  pin value (VCC/GND)
 */
uint8_t gpio_read(uint8_t,volatile uint8_t *);





#endif