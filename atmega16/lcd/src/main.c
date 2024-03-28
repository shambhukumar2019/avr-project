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

#include "common.h"



void main(void)
{
    gpio_port_mode(LCD_PORT,OUTPUT);
    gpio_port_mode(LCD_CRTL_PORT,OUTPUT);

    lcd_init(); // initialize 16x2 LCD
    
    

    for(;;)
    {
        lcd_send_word("HELLO LCD");
        _delay_ms(1000);
    }
}
