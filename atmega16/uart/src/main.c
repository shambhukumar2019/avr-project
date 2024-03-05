/**
 * @file main.c
 * @author shambhu kumar (you@domain.com)
 * @brief main driver code for uart
 * @version 0.1
 * @date 2024-02-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "m16_uart.h"


void main(void)
{
    uart_init(BAUD_9600);   // initiallize uart with given baud rate

    SET_GLOBAL_INTERRUPT;

    for(;;)
    {
        // eternal loop
    }
}