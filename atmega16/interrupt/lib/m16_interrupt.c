/**
 * @file m16_interrupt.c
 * @author shambhu kumar (you@domain.com)
 * @brief function definitions of interrupt header file
 * @version 0.1
 * @date 2024-01-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "m16_interrupt.h"



/**
 * @brief configure given interrupt
 * 
 * @param int_type type of interrupt from enum "interrupt_type"
 * @param int_mode ENABLE or DISABLE the interrupt
 * @param trig_mode LEVEL, RISING_EDGE, FALLING_EDGE (only for external interrupts)
 * 
 * @return void
 */
void config_interrupt(volatile uint8_t int_type,volatile uint8_t int_mode,volatile uint8_t trig_mode)
{

}


/**
 * @brief clear the flag of given interrupt
 * 
 * @param int_type type of interrupt from enum "interrupt_type" to clear its flag
 * 
 * @return void
 */
void clear_interrupt_flag(volatile uint8_t int_type)
{
    
}