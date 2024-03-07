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



#define NORMAL_SPEED        FALSE
#define DOUBLE_SPEED        TRUE

#define MASTER_MODE         TRUE
#define SLAVE_MODE          FALSE


#define SPI_F_CPU_BY_4      0
#define SPI_F_CPU_BY_16     1
#define SPI_F_CPU_BY_64     2
#define SPI_F_CPU_BY_128    3

#define SPI_DOUBLE_SPEED                    SET_BIT(SPI_FLAGS_REG,SPI2X)
#define SPI_NORMAL_SPEED                    CLEAR_BIT(SPI_FLAGS_REG,SPI2X)

#define SPI_CLOCK_SELECT(clock,speed)       if(speed == NORMAL_SPEED){\
                                                SPI_NORMAL_SPEED;\
                                            }\
                                            else if(speed == DOUBLE_SPEED){\
                                                SPI_DOUBLE_SPEED;\
                                            }\
                                            SPI_CONTROL_REG |= (clock<<0);\



#define ENABLE_SPI_INTERRUPT                ENABLE_INTERRUPT(SPI_CONTROL_REG,SPIE)
#define DISABLE_SPI_INTERRUPT               DISABLE_INTERRUPT(SPI_CONTROL_REG,SPIE)



#define SPI_ENABLE                          SET_BIT(SPI_CONTROL_REG,SPE)

#define SPI_MASTER_MODE(clock,speed)        DDRB |= (1<<SPI_MOSI_PIN) | (1<<SPI_SCK_PIN);\
                                            SPI_ENABLE;\
                                            SPI_CLOCK_SELECT(clock,speed);\

#define SPI_SLAVE_MODE                      DDRB |= (1<<SPI_MISO_PIN);\
                                            SPI_ENABLE;\




void spi_init(uint8_t);





#endif