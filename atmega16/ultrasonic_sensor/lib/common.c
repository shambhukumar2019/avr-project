#include "common.h"


/**
 * @brief store recieved data from spi isr
 * 
 */
uint8_t spdr_rx_byte = 0;
volatile uint8_t overflow_counter = 0;