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
    uint8_t data_high_byte = 0;
    uint8_t data_low_byte = 0;
    uint32_t data = 0;

    SET_GLOBAL_INTERRUPT;

    uart_init();

    spi_init(MASTER_MODE);  // initiallize spi in master mode
    

    for(;;)
    {
        SPI_SS_LOW;

        spi_send_byte(0x06);
        data_high_byte = spi_send_byte(0x40);
        data_high_byte &= (0x0F);
        data_low_byte = spi_send_byte(0x00);

        data = (data_high_byte << 8) | data_low_byte;

        SPI_SS_HIGH;
        uart_send_string("ADC Value: ");
        data *= 500;
        data = (data / 4096) * 10;
        uart_send_integer(data);
        uart_send_string(" mV\n");

        _delay_ms(1000);
    }
}
