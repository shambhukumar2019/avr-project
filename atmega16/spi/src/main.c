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



void main(void)
{
    spi_init(MASTER_MODE);  // initiallize spi in master mode


    for(;;)
    {
        // eternal loop
    }
}