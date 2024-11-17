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



/*

void ms_delay(uint16_t milli)
{
    uint16_t l_cnt = 0;

    while (l_cnt <= milli)
    {
       / * l_cnt += 1;
        TCNT0 = 0;
        OCR0 = 43U;  // for 1ms delay
        CLEAR_FLAG(TIMER_FLAGS_REG,T0_COMPARE_FLAG);
        TCCR0 = 0x0C;   //ctc mode clk/256
        while (POLL_BIT(TIMER_FLAGS_REG,T0_COMPARE_FLAG) == 0);
        CLEAR_FLAG(TIMER_FLAGS_REG,T0_COMPARE_FLAG);
        TCCR0 = 0;  // stop timer* /
    }
}



void us_delay(uint16_t micro)
{
    uint16_t l_cnt = 0;
    while(l_cnt <= micro)
    {
        l_cnt += 1;
        __asm("nop");
        __asm("nop");
        __asm("nop");
    }
}



void pwm(uint16_t freq,uint8_t dc,uint8_t oc_pin)
{
    / *

    /// on OC2 pin
    gpio_pin_mode(T2_OC_PIN,&PORTD,OUTPUT); // for fast pwm generation OC2 pin
    TCNT2 = 0;
    OCR2 = (25500U / dc); // set ocr2 for given duty cycle (dc)
    CLEAR_FLAG(TIMER_FLAGS_REG,T2_OVERFLOW_FLAG);
    // clk/64 fast pwm mode clear OC2 on compare match and set at bottom
    TCCR2 = 0x6B;   // fpwm = 675* /
}
*/

// generate 50 Hz pwm on oc0b pin
void pwm_oc0b(volatile uint8_t ton_factor_oc0b)
{
    //DDRD |= (1<<5); //oc0b as output, PD5 = oc0b
//     /// on OC0 pin
//     gpio_pin_mode(T0_OC_PIN,&PORTB,OUTPUT); // for fast pwm generation OC2 pin
    TCNT0 = 0;

	OCR0B = ((ton_factor_oc0b * 255U) / 100U);
    CLEAR_FLAG(TIFR0,TOV0);
	TCCR0A = 0x23;   // pwm on oc0b pin, top = 0xff
	TCCR0B = 0x05;	// clk/1024, fast pwm, f = 60.035Hz
}

/*

/// @brief generate pwm on OC2 pin of given frequency and duty cycle
/// @param frequency set pwm frequency
/// @param dc set pwm duty cycle
void pwm_oc2(pwm_freq frequency,uint8_t dc)
{/ *
    uint16_t l_dc = 0;

    l_dc = (255U * dc) / 100U;   // find OCR2 value for given duty cycle(dc)

    /// on OC0 pin
    gpio_pin_mode(T2_OC_PIN,&PORTD,OUTPUT); // for fast pwm generation OC2 pin
    TCNT2 = 0;

    OCR2 = l_dc;
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
    }* /

}*/

/*

void pwm_oc1a(volatile uint8_t ton_factor_oc1a)
{
    gpio_pin_mode(T1_OC_A_PIN,&PORTD,OUTPUT); // for fast pwm generation OC1A pin
    TCNT1 = 0;

    ICR1 = 43U;
    OCR1A = (43U * dc) / 100U;
    CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);
    TCCR1A = 0x82;  // top = ICR1, pwm on OC1A pin
    TCCR1B = 0x1C;  // clk/256

}*/

// generate 50 Hz pwm on oc1b pin
void pwm_oc1a(volatile uint8_t ton_factor_oc1a)
{    
	//gpio_pin_mode(T1_OC_B_PIN,&PORTB,OUTPUT); // for fast pwm generation OC1B pin
	//DDRB |= (1<<2); //oc1b as output, PB2
    TCNT1 = 0;	
	
	ICR1 = 20000U;//top 
	// (on_time_factor * (20000/20))/100
	OCR1A = 10U * ton_factor_oc1a;//duty cycle
	CLEAR_FLAG(TIMER1_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);
	TCCR1A = 0x82;  // top = ICR1, pwm on OC1A pin
	TCCR1B = 0x12;  // clk/8, f = 50Hz
}

/*


void config_timer(uint8_t timer,uint8_t oper_mode,uint16_t delay)
{

}



uint16_t measure_frequency(void)
{/ *
    volatile uint16_t l_icp_cnt = 0;

    gpio_pin_mode(T1_ICP_PIN,&PORTD,INPUT);

    ENABLE_ICP_RISE_EDGE;

    // measure frequency using ICP of timer 1

    //  get 1st timestamp of rising edge 
    while ((TIFR & (1<<ICF1)) == 0);
    l_icp_cnt = ICR1;
    CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);

    //  get 2nd timestamp of rising edge 
    while ((TIFR & (1<<ICF1)) == 0);
    l_icp_cnt = ICR1 - l_icp_cnt;   // pulse time period width
    CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);

    // if(l_icp_cnt > ICR1)
    //     // handle if overflow occurs
    DISABLE_ICP;

    l_icp_cnt = F_CPU / l_icp_cnt;  // calculate pulse frequency

    return l_icp_cnt;* /
}



uint8_t measure_dutycycle(void)
{/ *
    volatile uint16_t l_icp_cnt_1 = 0;
    volatile uint16_t l_icp_cnt_2 = 0;
    volatile uint16_t l_icp_cnt_3 = 0;
    uint32_t l_dc = 0;

    gpio_pin_mode(T1_ICP_PIN,&PORTD,INPUT);

    // measure duty cycle using ICP of timer 1
    ENABLE_ICP_RISE_EDGE;

    //  get 1st timestamp of rising edge 
    while ((TIFR & (1<<ICF1)) == 0);
    l_icp_cnt_1 = ICR1;
    CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);

    ENABLE_ICP_FALL_EDGE;

    //  get 1st timestamp of falling edge 
    while ((TIFR & (1<<ICF1)) == 0);
    l_icp_cnt_2 = ICR1;
    CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);

    ENABLE_ICP_RISE_EDGE;

    //  get 2nd timestamp of rising edge 
    while ((TIFR & (1<<ICF1)) == 0);
    l_icp_cnt_3 = ICR1;
    CLEAR_FLAG(TIMER_FLAGS_REG,T1_INPUT_CAPTURE_FLAG);

    DISABLE_ICP;


    l_dc = l_icp_cnt_2 - l_icp_cnt_1;
    l_dc = l_dc * 100U;
    l_icp_cnt_1 = l_icp_cnt_3 - l_icp_cnt_1;
    l_dc = l_dc / l_icp_cnt_1;  // duty cycle

    return (uint8_t)l_dc;* /
}*/

