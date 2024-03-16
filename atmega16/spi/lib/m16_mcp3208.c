#include "m16_mcp3208.h"

uint16_t adc_value_mcp3208 = 0;


/**
 * @brief intialize mcp3208 ADC
 * 
 */
void adc_init_mcp3208(void)
{
    spi_init(MASTER_MODE);  // initilize master mode spi for commun. with mcp3208 slave spi
}


/**
 * @brief read converted digital value from given channel
 * 
 * @param channel read voltage from channel
 */
static void read_adc_mcp3208(uint8_t channel)
{
    uint8_t cmd_byte = 0;
    uint8_t data_high_byte = 0;
    uint8_t data_low_byte = 0;

    //  bit 2 -> start adc operation, bit 1 -> single ended channel mode
    cmd_byte = 0b00000110 | (channel >> 2); // to add channel above 3 in command


    SPI_SS_LOW; // select the slave

    #if (MCP3208_ADC_INTERRUPT == DISABLE)
    {
        uart_send_string("\n***POLL***\n");
        spi_send_byte(cmd_byte);    // send start byte
        channel <<= 6;  // command for 1st 3 channel selection
        data_high_byte = spi_send_byte(channel);   // send channel select byte, recieve adc high byte
        data_high_byte &= (0x0F);
        data_low_byte = spi_send_byte(0x00);    // send xx, recieve adc low byte
    }
    #elif (MCP3208_ADC_INTERRUPT == ENABLE)
    {
        uart_send_string("\n***ISR***\n");
        SPDR = cmd_byte;    // send start byte
        _delay_us(20);
        // _delay_ms(1);
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        channel <<= 6;  // command for 1st 3 channel selection
        SPDR = channel;   // send channel select byte, recieve adc high byte
        // _delay_ms(1);
        _delay_us(20);
        __asm__("nop"); // to give time for isr to update values
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        data_high_byte = adc_high_byte & (0x0F);
        SPDR = 0x00;    // send xx, recieve adc low byte
        _delay_us(20);   
        // _delay_ms(1);
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        data_low_byte = adc_low_byte;
    }
    #endif

    adc_value_mcp3208 = (data_high_byte << 8) | data_low_byte;

    SPI_SS_HIGH;    // abort communication with slave
}


/**
 * @brief read and convert digital value into milli volts value from given channel
 * 
 * @param adc_channel read voltage from channel
 * @return uint16_t milli volts value
 */
uint16_t read_millivolt_mcp3208(uint8_t adc_channel)
{
    uint32_t l_adc_val = 0;

    //  read digital value of voltage from adc_channel in variable "adc_value_mcp3208"
    read_adc_mcp3208(adc_channel);

    l_adc_val = ((uint32_t)adc_value_mcp3208 * V_REF_MCP3208);
    l_adc_val = (l_adc_val / 4096) * 10;  // convert to milli volts

    return l_adc_val;
}


/* //  ************************** //

static void read_adc(uint8_t channel)
{
    uint8_t cmd_byte = 0;
    uint8_t data_high_byte = 0;
    uint8_t data_low_byte = 0;

    //  bit 2 -> start adc operation, bit 1 -> single ended channel mode
    cmd_byte = 0b00000110 | (channel >> 2); // to add channel above 3 in command


    SPI_SS_LOW; // select the slave

    spi_send(cmd_byte);    // send start byte
    _delay_us(20);
    // _delay_ms(1);
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    channel <<= 6;  // command for 1st 3 channel selection
    spi_send(channel);   // send channel select byte, recieve adc high byte
    // _delay_ms(1);
    _delay_us(20);
    __asm__("nop"); // to give time for isr to update values
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    data_high_byte = adc_high_byte & (0x0F);
    spi_send(0x00);    // send xx, recieve adc low byte
     _delay_us(20);   
    // _delay_ms(1);
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    data_low_byte = adc_low_byte;
    adc_value_mcp3208 = (data_high_byte << 8) | data_low_byte;

    SPI_SS_HIGH;    // abort communication with slave

    // DISABLE_SPI_INTERRUPT;
}


/**
 * @brief read and convert digital value into milli volts value from given channel
 * 
 * @param adc_channel read voltage from channel
 * @return uint16_t milli volts value
 */
/*
uint16_t read_millivolt(uint8_t adc_channel)
{
    uint32_t l_adc_val = 0;

    read_adc(adc_channel);

    l_adc_val = ((uint32_t)adc_value_mcp3208 * V_REF_MCP3208);
    l_adc_val = (l_adc_val / 4096) * 10;  // convert to milli volts

    return l_adc_val;
} */