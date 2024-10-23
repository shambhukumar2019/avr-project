/**
 * @file m16_isr.c
 * @author shambhu kumar (you@domain.com)
 * @brief define all ISR(interrupt sub-routines) in this file
 * @version 0.1
 * @date 2024-01-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "m16_interrupt.h"
// #include "m16_uart.h"

volatile uint8_t tx_ds_flag = 0;
volatile uint8_t rx_dr_flag = 0;

// counter to be used in SPI ISR
//volatile uint8_t spi_isr_counter = 0;


//ADC interrupt when conversion completes
ISR(ADC_vect)
{
	/*TIFR |= (1<<OCF1B);	//clear compare flag for next conversion to start
	TCNT1 = 0;			//reset counter for next round
	
	//read ADC digital value
	adc_digital_value = ADCW;	//in millivolts, step size => 4.88mV
    // uart_send_integer(adc_digital_value);
	adc_read_flag = 1;*/
}


/**
 * @brief executes when spi transfer completed
 * 
 */
ISR(SPI_STC_vect)
{
    /*spdr_rx_byte = SPDR;    // recieved data from SPI device

    // enable "MCP3208_ADC_INTERRUPT" if using mcp3208 for ADC with interrupt
    #if (MCP3208_ADC_INTERRUPT == ENABLE)
    {
        spi_isr_counter++;
        if (spi_isr_counter == 2)
        {
            adc_high_byte = spdr_rx_byte;
        }
        else if(spi_isr_counter == 3)
        {
            adc_low_byte = spdr_rx_byte;
            spi_isr_counter = 0;
        }
    }
    #endif*/
}

ISR(INT0_vect)
{
	tx_ds_flag = 1;
    //GPIO_PIN_HIGH(PORTC,PORTC0);
	PORTC = 0x02;
}

ISR(TIMER0_OVF_vect)
{
    //CLEAR_FLAG(TIMER_FLAGS_REG,T0_OVERFLOW_FLAG);
    /* count++;
    if(count >= 50)
    {
        count = 0;
        GPIO_PIN_TOGGLE(PORTA,PIN0);
    }
    TCNT0 = 0x00; */
    // GPIO_PIN_TOGGLE(PORTA,PIN0);
    // TCNT0 = 250;
}

ISR(TIMER0_COMPA_vect)
{
    //OCR0 = 250;
}

/// @brief using for ultrasonic sensor
/// @param  overflow interrupt 
ISR(TIMER1_OVF_vect)
{
    //overflow_counter += 1;
}

ISR(TIMER1_COMPA_vect)
{
      
    
}

ISR(TIMER1_CAPT_vect)
{
    /* f1 = ICR1;
    if (count == 0)
    {
        f2 = f1;
        count++;
    }
    else
    {
        count = 0;
        f2 = f1 - f2;
        TIMSK &= ~(1<<TICIE1);
    } */
}

ISR(USART_UDRE_vect)
{
   UDR0 = uart.uart_tx_buffer[uart.uart_tx_index++];
   if (uart.uart_tx_buffer[uart.uart_tx_index] == '\0')
   {
        //DISABLE_UART_UDRE_INTERRUPT;
        uart.uart_tx_index = 0;
        //ENABLE_UART_RX_INTERRUPT;
   }
   
}


ISR(USART_RX_vect)
{
    uart.uart_rx_buffer[uart.uart_rx_index] = UDR0;
    uart.uart_rx_index++;
    if(uart.uart_rx_buffer[uart.uart_rx_index - 1] == '\n')
    {
        uart.uart_rx_buffer[uart.uart_rx_index - 1] = '\n';
        uart.uart_rx_buffer[uart.uart_rx_index] = '\0';
        string_copy(uart.uart_buffer,uart.uart_rx_buffer);
        uart.uart_rx_index = 0;
        uart.uart_rx_complete_flag = 1;
    }
}

ISR(BADISR_vect)
{
    
}


