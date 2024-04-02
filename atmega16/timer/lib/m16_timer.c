/**
 * @file m16_timer.c
 * @author shambhu kumar (you@domain.com)
 * @brief source code for timer device driver of atmega16
 * @version 0.1
 * @date 2024-03-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "m16_timer.h"




void ms_delay(uint16_t milli)
{
    uint16_t l_cnt = 0;

    while (l_cnt <= milli)
    {
        l_cnt += 1;
        TCNT0 = 0;
        OCR0 = 43;  // for 1ms delay
        CLEAR_FLAG(TIMER_FLAGS_REG,T0_COMPARE_FLAG);
        TCCR0 = 0x0C;   //ctc mode clk/256
        while (POLL_BIT(TIMER_FLAGS_REG,T0_COMPARE_FLAG) == 0);
        CLEAR_FLAG(TIMER_FLAGS_REG,T0_COMPARE_FLAG);
        TCCR0 = 0;  // stop timer
    }
}



void us_delay(uint16_t micro)
{
    uint16_t l_cnt = 0;
    while(l_cnt <= micro)
    {
        l_cnt += 1;
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
    }
}



void pwm(uint16_t freq,uint8_t dc,uint8_t oc_pin)
{
    

    /// on OC2 pin
    gpio_pin_mode(T2_OC_PIN,&PORTD,OUTPUT); // for fast pwm generation OC2 pin
    TCNT2 = 0;
    OCR2 = (25500U / dc); // set ocr2 for given duty cycle (dc)
    CLEAR_FLAG(TIMER_FLAGS_REG,T2_OVERFLOW_FLAG);
    // clk/64 fast pwm mode clear OC2 on compare match and set at bottom
    TCCR2 = 0x6B;   // fpwm = 675
}


void pwm_oc0(pwm_freq frequency,uint8_t dc)
{
    volatile uint8_t l_dc = 0;

    l_dc = (25500U / dc);   // find OCR0 value for given duty cycle(dc)

    /// on OC0 pin
    gpio_pin_mode(T0_OC_PIN,&PORTB,OUTPUT); // for fast pwm generation OC0 pin
    TCNT0 = 0;

    #if (FREQ_675 == frequency)
    {
        OCR0 = l_dc;
        CLEAR_FLAG(TIMER_FLAGS_REG,T0_OVERFLOW_FLAG);
        // clk/64 fast pwm mode clear OC0 on compare match and set at bottom
        TCCR0 = 0x6B;   // fpwm = 675Hz
    }
    #elif (FREQ_5400 == frequency)
    {
        OCR0 = l_dc;
        CLEAR_FLAG(TIMER_FLAGS_REG,T0_OVERFLOW_FLAG);
        // clk/8 fast pwm mode clear OC0 on compare match and set at bottom
        TCCR0 = 0x6A;   // fpwm = 5400Hz
    }
    #elif (FREQ_43200 == frequency)
    {
        OCR0 = l_dc;
        CLEAR_FLAG(TIMER_FLAGS_REG,T0_OVERFLOW_FLAG);
        // clk/1 fast pwm mode clear OC0 on compare match and set at bottom
        TCCR0 = 0x69;   // fpwm = 43200Hz
    }
    #endif

}

void pwm_oc2(pwm_freq frequency,uint8_t dc)
{
    volatile uint8_t l_dc = 0;

    l_dc = (25500U / dc);   // find OCR2 value for given duty cycle(dc)

    /// on OC0 pin
    gpio_pin_mode(T2_OC_PIN,&PORTD,OUTPUT); // for fast pwm generation OC2 pin
    TCNT2 = 0;

    #if (FREQ_675 == frequency)
    {
        OCR2 = l_dc;
        CLEAR_FLAG(TIMER_FLAGS_REG,T0_OVERFLOW_FLAG);
        // clk/64 fast pwm mode clear OC2 on compare match and set at bottom
        TCCR2 = 0x6B;   // fpwm = 675Hz
    }
    #elif (FREQ_5400 == frequency)
    {
        OCR2 = l_dc;
        CLEAR_FLAG(TIMER_FLAGS_REG,T0_OVERFLOW_FLAG);
        // clk/8 fast pwm mode clear OC2 on compare match and set at bottom
        TCCR2 = 0x6A;   // fpwm = 5400Hz
    }
    #elif (FREQ_43200 == frequency)
    {
        OCR2 = l_dc;
        CLEAR_FLAG(TIMER_FLAGS_REG,T0_OVERFLOW_FLAG);
        // clk/1 fast pwm mode clear OC2 on compare match and set at bottom
        TCCR2 = 0x69;   // fpwm = 43200Hz
    }
    #endif

}



void config_timer(uint8_t timer,uint8_t oper_mode,uint16_t delay)
{

}



uint16_t measure_frequency(void)
{

}



uint8_t measure_dutycycle(void)
{

}

