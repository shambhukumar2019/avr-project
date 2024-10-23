#include "common.h"


/**
 * @brief store recieved data from spi isr
 * 
 */
volatile uint8_t spdr_rx_byte = 0;