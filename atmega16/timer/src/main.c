/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief main driver code
 * @version 0.1
 * @date 2024-03-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "common.h"



void main(void)
{
    //  input capture mode
    // GPIO_PULLUP_ON(PORTD,T1_ICP_PIN);
    // gpio_pin_mode(T1_ICP_PIN,&PORTD,INPUT);
    
    //clear oc1b on compare match and set on bottom, non inverting
    // TCCR1A = 0;
    // TCCR1B = 0x41;  // clk   icp on rising edge 
    
    
    gpio_pin_mode(T1_OC_A_PIN,&PORTD,OUTPUT);   // for fast pwm mode on oc1A pin
    TCNT1 = 0;  // initialize timer 1
    ICR1 = 431;  //100Hz, TOP value
    OCR1A = 431;  // Duty cycle = 100%
    CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);
    TCCR1A = 0x82;  // top = ICR1, pwm on OC1A pin
    TCCR1B = 0x1C;  // clk/256
    
    
    
    /* uint16_t f = 0;

    // measure frequency using ICP of timer 1
    while ((TIFR & (1<<ICF1)) == 0);
    f = ICR1;
    CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);

    while ((TIFR & (1<<ICF1)) == 0);
    f = ICR1 - f;
    // CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);
    
    PORTA = f>>8; */

    for(;;)
    {
        // PORTA = f2>>8;
        
    }
}