/**
 * @file main.c
 * @author shambhu kumar (you@domain.com)
 * @brief driver code for SPI
 * @version 0.1
 * @date 2024-03-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "m16_spi.h"

/**
 * @brief MASTER MODE
 * 
 */

void main(void)
{
    gpio_pin_mode(PA0,&PORTA,OUTPUT);
    spi_init(MASTER_MODE);  // initiallize spi in master mode

    
    for(;;)
    {
        SPDR = 0x01;
        POLL_BIT(SPI_FLAGS_REG,SPI_FLAG);
        _delay_ms(1000);
    }
}