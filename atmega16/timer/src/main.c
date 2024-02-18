#include "timer.h"



void main(void)
{    
    gpio_pin_mode(TIMER0_OC_PIN,&PORTB,OUT);
    //TCCR0 = 0x05;   //normal mode clk/1024
    //TCCR0 = 0x0d;   //ctc mode clk/1024
    TCCR0 = 0x1d;   //ctc mode clk/1024, toggle OC0 on compare match

    //clear_interrupt_flag(TIMER0_OVERFLOW_INTERRUPT);  
    //config_interrupt(TIMER0_OVERFLOW_INTERRUPT,ENABLE,0);   // enable T0 overflow interrupt

    CLEAR_FLAG(TIMER_FLAGS_REG,T0_COMPARE_FLAG);
    config_interrupt(TIMER0_COMPARE_MATCH_INTERRUPT,ENABLE,0);   // enable T0 compare interrupt
    
    //TCNT0 = 39; // for 20ms delay
    
    //OCR0 = 0xd8;    // 216 for 20 ms delay 
    OCR0 = 214; // oc0 pin toggle once on compare match 40ms
    SET_GLOBAL_INTERRUPT;

    for(;;)
    {
        
    }
}