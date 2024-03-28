/**
 * @file keypad.c
 * @author your name (you@domain.com)
 * @brief keypad driver source code
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "keypad.h"


/**
 * @brief 4x4 keypad lookup table
 * 
 */
uint8_t keypad_lookup[][4] = {  {'1','2','3','A'},
                                {'4','5','6','B'},
                                {'7','8','9','C'},
                                {'*','0','#','D'}   };


/**
 * @brief initiallize keypad I/O's
 * 
 */
void keypad_init(void)
{
    KEYPAD_DDR |= (1<<R0) | (1<<R1) | (1<<R2) | (1<<R3);      // rows o/p
    KEYPAD_DDR &= ~((1<<C0) | (1<<C1) | (1<<C2) | (1<<C3));   // columns i/p

    KEYPAD_PORT |= (1<<C0) | (1<<C1) | (1<<C2) | (1<<C3);     // pull-up input column pins
    KEYPAD_PORT |= (1<<R0) | (1<<R1) | (1<<R2) | (1<<R3);     // high logic at output rows
    
}


/**
 * @brief read the pressed key on 4x4 keypad
 * 
 * @return uint8_t key pressed
 */
uint8_t keypad_scan(void)
{
    volatile uint8_t l_pin_val = 0;
    uint8_t row_index = 0, coln_index = 0;
    
    //0b00001111
    for (row_index = 0; row_index < 4; row_index++)
    {
        GPIO_PIN_LOW(KEYPAD_PORT,row_index);    // low each row o/p to get which coln pressed
        for(coln_index = 0; coln_index < 4;coln_index++)
        {
            //  read each coln value for respective row
            l_pin_val = (KEYPAD_PIN & (0x10 << coln_index));    
            if(l_pin_val == 0)
            {
                //  make scanned row o/p high again
                GPIO_PIN_HIGH(KEYPAD_PORT,row_index);
                //  return pressed key based on row, coln postion from keypad lookup table
                return keypad_lookup[row_index][coln_index];
            }
        }
        //  make scanned row o/p high again
        GPIO_PIN_HIGH(KEYPAD_PORT,row_index);
    }

    return 0xff;    // if key not pressed
}
