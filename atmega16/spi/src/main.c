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
    uart_init();

    gpio_port_mode(&PORTA,OUTPUT);
    spi_init(SLAVE_MODE);  // initiallize spi in master mode

    uint8_t v = 0;

    SET_GLOBAL_INTERRUPT;
    
    for(;;)
    {
        POLL_BIT(SPI_FLAGS_REG,SPI_FLAG);
        v = SPDR;
        PORTA = v;
        if(uart.uart_rx_complete_flag == 1)
        {
            uart_send_string(uart.uart_buffer);
        }
        uart_send_integer(v);
        v++;
        _delay_ms(1000);
    }
}