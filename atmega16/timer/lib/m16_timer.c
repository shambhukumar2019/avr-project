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
    volatile uint16_t l_dc = 0;

    l_dc = (255U * dc) / 100;   // find OCR0 value for given duty cycle(dc)

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
    volatile uint16_t l_dc = 0;

    l_dc = (255U * dc) / 100U;   // find OCR2 value for given duty cycle(dc)

    /// on OC0 pin
    gpio_pin_mode(T2_OC_PIN,&PORTD,OUTPUT); // for fast pwm generation OC2 pin
    TCNT2 = 0;

    OCR2 = (uint8_t)l_dc;
    CLEAR_FLAG(TIMER_FLAGS_REG,T2_OVERFLOW_FLAG);

    switch(frequency)
    {
        case FREQ_675:
        {
            // clk/64 fast pwm mode clear OC2 on compare match and set at bottom
            TCCR2 = 0x6C;   // fpwm = 675Hz
            break;
        }
        case FREQ_1350:
        {
            // clk/8 fast pwm mode clear OC2 on compare match and set at bottom
            TCCR2 = 0x6B;   // fpwm = 5400Hz
            break;
        }
        case FREQ_5400:
        {
            // clk/8 fast pwm mode clear OC2 on compare match and set at bottom
            TCCR2 = 0x6A;   // fpwm = 5400Hz
            break;
        }
        case FREQ_43200:
        {
            // clk/1 fast pwm mode clear OC2 on compare match and set at bottom
            TCCR2 = 0x69;   // fpwm = 43200Hz
            break;
        }
        default:
        {
            //  error code
            break;
        }
    }

}


void pwm_oc1a(pwm_freq frequency,uint8_t dc)
{
    gpio_pin_mode(T1_OC_A_PIN,&PORTD,OUTPUT); // for fast pwm generation OC1A pin
    TCNT1 = 0;

    #if (FREQ_100 == frequency)
    {
        ICR1 = 431U;
        OCR1A = (431U * dc) / 100U;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);
        TCCR1A = 0x82;  // top = ICR1, pwm on OC1A pin
        TCCR1B = 0x1C;  // clk/256
    }
    #elif (FREQ_200 == frequency)
    {
        ICR1 = 215U;
        OCR1A = (215U * dc) / 100U;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);
        TCCR1A = 0x82;  // top = ICR1, pwm on OC1A pin
        TCCR1B = 0x1C;  // clk/256
    }
    #elif (FREQ_300 == frequency)
    {
        ICR1 = 143U;
        OCR1A = (143U * dc) / 100U;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);
        TCCR1A = 0x82;  // top = ICR1, pwm on OC1A pin
        TCCR1B = 0x1C;  // clk/256
    }
    #elif (FREQ_400 == frequency)
    {
        ICR1 = 107U;
        OCR1A = (107U * dc) / 100U;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);
        TCCR1A = 0x82;  // top = ICR1, pwm on OC1A pin
        TCCR1B = 0x1C;  // clk/256
    }
    #elif (FREQ_500 == frequency)
    {
        ICR1 = 86U;
        OCR1A = (86U * dc) / 100U;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);
        TCCR1A = 0x82;  // top = ICR1, pwm on OC1A pin
        TCCR1B = 0x1C;  // clk/256
    }
    #elif (FREQ_600 == frequency)
    {
        ICR1 = 71U;
        OCR1A = (71U * dc) / 100U;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);
        TCCR1A = 0x82;  // top = ICR1, pwm on OC1A pin
        TCCR1B = 0x1C;  // clk/256
    }
    #elif (FREQ_700 == frequency)
    {
        ICR1 = 61U;
        OCR1A = (61U * dc) / 100U;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);
        TCCR1A = 0x82;  // top = ICR1, pwm on OC1A pin
        TCCR1B = 0x1C;  // clk/256
    }
    #elif (FREQ_800 == frequency)
    {
        ICR1 = 53U;
        OCR1A = (53U * dc) / 100U;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);
        TCCR1A = 0x82;  // top = ICR1, pwm on OC1A pin
        TCCR1B = 0x1C;  // clk/256
    }
    #elif (FREQ_900 == frequency)
    {
        ICR1 = 47U;
        OCR1A = (47U * dc) / 100U;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);
        TCCR1A = 0x82;  // top = ICR1, pwm on OC1A pin
        TCCR1B = 0x1C;  // clk/256
    }
    #elif (FREQ_1000 == frequency)
    {
        ICR1 = 43U;
        OCR1A = (43U * dc) / 100U;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);
        TCCR1A = 0x82;  // top = ICR1, pwm on OC1A pin
        TCCR1B = 0x1C;  // clk/256
    }
    #endif

}


void pwm_oc1b(pwm_freq frequency,uint8_t dc)
{
    gpio_pin_mode(T1_OC_B_PIN,&PORTD,OUTPUT); // for fast pwm generation OC1B pin
    TCNT1 = 0;

    #if (FREQ_100 == frequency)
    {
        OCR1A = 431U;
        OCR1B = (431U * dc) / 100U;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_COMPARE_A_FLAG);
        TCCR1A = 0x23;  // top = OCR1A, pwm on OC1B pin
        TCCR1B = 0x1C;  // clk/256
    }
    #elif (FREQ_200 == frequency)
    {
        OCR1A = 215U;
        OCR1B = (215U * dc) / 100U;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_COMPARE_A_FLAG);
        TCCR1A = 0x23;  // top = OCR1A, pwm on OC1B pin
        TCCR1B = 0x1C;  // clk/256
    }
    #elif (FREQ_300 == frequency)
    {
        OCR1A = 143U;
        OCR1B = (143U * dc) / 100U;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_COMPARE_A_FLAG);
        TCCR1A = 0x23;  // top = OCR1A, pwm on OC1B pin
        TCCR1B = 0x1C;  // clk/256
    }
    #elif (FREQ_400 == frequency)
    {
        OCR1A = 107U;
        OCR1B = (107U * dc) / 100U;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_COMPARE_A_FLAG);
        TCCR1A = 0x23;  // top = OCR1A, pwm on OC1B pin
        TCCR1B = 0x1C;  // clk/256
    }
    #elif (FREQ_500 == frequency)
    {
        OCR1A = 86U;
        OCR1B = (86U * dc) / 100U;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_COMPARE_A_FLAG);
        TCCR1A = 0x23;  // top = OCR1A, pwm on OC1B pin
        TCCR1B = 0x1C;  // clk/256
    }
    #elif (FREQ_600 == frequency)
    {
        OCR1A = 71U;
        OCR1B = (71U * dc) / 100U;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_COMPARE_A_FLAG);
        TCCR1A = 0x23;  // top = OCR1A, pwm on OC1B pin
        TCCR1B = 0x1C;  // clk/256
    }
    #elif (FREQ_700 == frequency)
    {
        OCR1A = 61U;
        OCR1B = (61U * dc) / 100U;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_COMPARE_A_FLAG);
        TCCR1A = 0x23;  // top = OCR1A, pwm on OC1B pin
        TCCR1B = 0x1C;  // clk/256
    }
    #elif (FREQ_800 == frequency)
    {
        OCR1A = 53U;
        OCR1B = (53U * dc) / 100U;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_COMPARE_A_FLAG);
        TCCR1A = 0x23;  // top = OCR1A, pwm on OC1B pin
        TCCR1B = 0x1C;  // clk/256
    }
    #elif (FREQ_900 == frequency)
    {
        OCR1A = 47U;
        OCR1B = (47U * dc) / 100U;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_COMPARE_A_FLAG);
        TCCR1A = 0x23;  // top = OCR1A, pwm on OC1B pin
        TCCR1B = 0x1C;  // clk/256
    }
    #elif (FREQ_1000 == frequency)
    {
        OCR1A = 43U;
        OCR1B = (43U * dc) / 100U;
        CLEAR_FLAG(TIMER_FLAGS_REG,T1_COMPARE_A_FLAG);
        TCCR1A = 0x23;  // top = OCR1A, pwm on OC1B pin
        TCCR1B = 0x1C;  // clk/256
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

