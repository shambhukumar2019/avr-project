/**
 * @file m16_spi.h
 * @author your name (you@domain.com)
 * @brief spi device driver header file
 * @version 0.1
 * @date 2024-03-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _SPI_H_
#define _SPI_H_


#include "common.h"

/**
 * @brief chnage between polling and interrupt methods for SPI
 * 
 */
#define SPI_WITH_INTERRUPT  DISABLE


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



#define NORMAL_SPEED        FALSE
#define DOUBLE_SPEED        TRUE

#define MASTER_MODE         TRUE
#define SLAVE_MODE          FALSE


#define SPI_F_CPU_BY_4      0
#define SPI_F_CPU_BY_16     1
#define SPI_F_CPU_BY_64     2
#define SPI_F_CPU_BY_128    3


/**
 * @brief define clock speed for SPI Master
 * 
 */
#define SPI_F_CPU   SPI_F_CPU_BY_4

#define SPI_FLAG                        SPIF
#define SPI_FLAGS_REG                   SPSR
#define SPI_CONTROL_REG                 SPCR


#define SPI_DOUBLE_SPEED                    SET_BIT(SPI_FLAGS_REG,SPI2X)
#define SPI_NORMAL_SPEED                    CLEAR_BIT(SPI_FLAGS_REG,SPI2X)

#define SPI_CLOCK_SELECT(clk,speed)       {	if(speed == DOUBLE_SPEED){\
                                                SPI_DOUBLE_SPEED;\
                                            }\
                                            SPI_CONTROL_REG |= (clk<<0);\
										  }



// #define ENABLE_SPI_INTERRUPT                ENABLE_INTERRUPT(SPI_CONTROL_REG,SPIE)
// #define DISABLE_SPI_INTERRUPT               DISABLE_INTERRUPT(SPI_CONTROL_REG,SPIE)


#define SPI_SS_HIGH                         GPIO_PIN_HIGH(PORTB,SPI_SS_PIN)
#define SPI_SS_LOW                          GPIO_PIN_LOW(PORTB,SPI_SS_PIN)


#define SPI_ENABLE                          SET_BIT(SPI_CONTROL_REG,SPE)
#define ENABLE_MASTER_MODE                  SET_BIT(SPI_CONTROL_REG,MSTR)

#define SPI_MASTER_MODE(clk,speed)			{DDRB |= (1<<SPI_MOSI_PIN) | (1<<SPI_SCK_PIN) | (1<<SPI_SS_PIN);\
                                            SPI_SS_HIGH;\
                                            SPI_CLOCK_SELECT(clk,speed);\
                                            ENABLE_MASTER_MODE;\
											SPI_ENABLE;}

#define SPI_SLAVE_MODE                      {DDRB |= (1<<SPI_MISO_PIN);\
                                            SPI_ENABLE;}



void spi_init(volatile uint8_t);

volatile uint8_t spi_rw_byte(volatile uint8_t);

// void spi_send(uint8_t);


#endif