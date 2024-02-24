#include "timer.h"



void main(void)
{
    gpio_pin_mode(TIMER1_OC_B_PIN,&PORTD,OUTPUT);   // for fast pwm mode on oc1b pin
    // gpio_pin_mode(TIMER0_OC_PIN,&PORTB,OUTPUT); // for fast pwm generation
    /* gpio_pin_mode(PIN0,&PORTA,OUTPUT);  //make pin 0 of porta output
    gpio_pin_mode(TIMER1_OC_A_PIN,&PORTD,OUTPUT);
    GPIO_PULLUP_ON(PORTB,EXT_T0_PIN);
    gpio_pin_mode(EXT_T0_PIN,&PORTB,INPUT); */
    
    //gpio_pin_mode(TIMER0_OC_PIN,&PORTB,OUT);    //make OC0 as output to toogle 
    
    //clear oc1b on compare match and set on bottom, non inverting
    TCCR1A = 0x23;
    TCCR1B = 0x1d;  // clk/1024 fast pwm TOP= ocr1a

    // clk/1024 fast pwm mode clear OC0 on compare match and set at bottom
    // TCCR0 = 0x6d;
    //TCCR0 = 0x05;   //normal mode clk/1024
    //TCCR0 = 0x0d;   //ctc mode clk/1024
    //TCCR0 = 0x1d;   //ctc mode clk/1024, toggle OC0 on compare match
    /* TCCR1A = 0x40;  //toggle oc1a on compare match
    TCCR1B = 0x0d;  // ctc mode clk/1024
    TCCR0 = 0x06;   // normal mode clk on t0 pin rising edge */
    TCNT1 = 0;
    OCR1A = 1000;  //Fpwm= 10.79 Hz, TOP value
    OCR1B = 500;  // Duty cycle = 50%
    // TCNT0 = 0;
    // OCR0 = 128; // for 50% duty cycle (ocr0 = 2.56 * dutycycle)
    //TCNT0 = 39; // for 20ms delay
    //OCR0 = 0xd8;    // ctc mode 216 for 20 ms delay 
    //OCR0 = 214; // oc0 pin toggle once on compare match 40ms
    /* OCR1A = 53999;  // 10s delay on oc1a pin
    TCNT0 = 250; // 1 min delay along with oc1a
    TCNT1 = 0; */


    //clear_interrupt_flag(TIMER0_OVERFLOW_INTERRUPT);  
    //config_interrupt(TIMER0_OVERFLOW_INTERRUPT,ENABLE,0);   // enable T0 overflow interrupt

    //CLEAR_FLAG(TIMER_FLAGS_REG,T0_COMPARE_FLAG);
    //config_interrupt(TIMER0_COMPARE_MATCH_INTERRUPT,ENABLE,0);   // enable T0 compare interrupt

    //CLEAR_FLAG(TIMER_FLAGS_REG,T1_COMPARE_A_FLAG);
    // CLEAR_FLAG(TIMER_FLAGS_REG,T0_OVERFLOW_FLAG);
    //config_interrupt(TIMER1_COMPARE_MATCH_A_INTERRUPT,ENABLE,0);
    // config_interrupt(TIMER0_OVERFLOW_INTERRUPT,ENABLE,0);
    
    
    //SET_GLOBAL_INTERRUPT;

    for(;;)
    {
        
    }
}