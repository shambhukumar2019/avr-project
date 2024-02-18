#include "timer.h"



void main(void)
{
    //TCCR0 = 0x05;   //normal mode clk/1024
    TCCR0 = 0x0d;   //ctc mode clk/1024
    //clear_interrupt_flag(TIMER0_OVERFLOW_INTERRUPT);  
    //config_interrupt(TIMER0_OVERFLOW_INTERRUPT,ENABLE,0);   // enable T0 overflow interrupt

    CLEAR_FLAG(TIMER_FLAGS_REG,T0_COMPARE_FLAG);
    config_interrupt(TIMER0_COMPARE_MATCH_INTERRUPT,ENABLE,0);   // enable T0 compare interrupt
    
    //TCNT0 = 39; // for 20ms delay
    TCNT0 = 0;
    OCR0 = 0xd8;    // 216 for 20 ms delay 
    SET_GLOBAL_INTERRUPT;

    // set pin as output to operate on
    gpio_pin_mode(PIN0,&PORTA,OUT);

    for(;;)
    {
        // statements
    }
}