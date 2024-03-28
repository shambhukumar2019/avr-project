/**
 * @file lcd_162.c
 * @author shambhu kumar (you@domain.com)
 * @brief source code for lcd device driver
 * @version 0.1
 * @date 2024-03-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "lcd_162.h"


/**
 * @brief send command to lcd
 * 
 * @param cmd_byte command for lcd
 */
void lcd_send_cmd(uint8_t cmd_byte)
{
    // LCD_PORT = HIGH_NIBBLE(cmd_byte);
    LCD_PORT = cmd_byte;
    LCD_CMD_MODE;
    LCD_ENABLE_PULSE;
    _delay_us(200); // delay required after each cmd
    /* LCD_PORT = LOW_NIBBLE(cmd_byte);
    LCD_ENABLE_PULSE;
    _delay_us(200);*/
}


/**
 * @brief send data to lcd
 * 
 * @param data_byte data for display on lcd
 */
void lcd_send_data(uint8_t data_byte)
{
    // LCD_PORT = HIGH_NIBBLE(data_byte);
    LCD_PORT = data_byte;
    LCD_DATA_MODE;
    LCD_ENABLE_PULSE;
    _delay_us(200); // delay required after each data
    /* LCD_PORT = LOW_NIBBLE(data_byte);
    LCD_ENABLE_PULSE;
    _delay_us(200); */
}


/**
 * @brief initialize 16x2 lcd for 4 bit mode
 * 
 */
void lcd_init(void)
{
    // let lcd initialize its peripherals
    _delay_ms(20);

    // lcd 4 bit mode initiallization
    // lcd_send_cmd(0x33);
    // lcd_send_cmd(0x32);
    // lcd_send_cmd(0x28);
    lcd_send_cmd(0x38);
    lcd_send_cmd(0x02);
    _delay_ms(3);
    lcd_send_cmd(0x0E); // display on cursor on

    // clear lcd display
    lcd_send_cmd(0x01);
    _delay_ms(3);   // delay required after clear cmd
}


/**
 * @brief send enable pulse for lcd
 * 
 */
void lcd_send_enable_pulse(void)
{
    SET_BIT(LCD_PORT,LCD_EN_PIN);
    _delay_us(1);   // min. enable pulse width required = 500ns
    CLEAR_BIT(LCD_PORT,LCD_EN_PIN);
}


/**
 * @brief send string to lcd
 * 
 * @param word strong to display on lcd
 */
void lcd_send_word(uint8_t *word)
{
    while ((*word) != NULL)
    {
        lcd_send_data(*word);
        word++;
    }   
}


/**
 * @brief set the cursor position at row and column
 * 
 * @param row set cursor row
 * @param column set cursor column
 */
void lcd_cursor_pos(uint8_t row ,uint8_t column)
{
    uint8_t l_row_cmd_array[] = {0x80,0xC0};

    lcd_send_cmd((l_row_cmd_array[row - 1] + (column - 1)));

}


/**
 * @brief clear entire lcd display
 * 
 */
void lcd_clear_disp(void)
{
    lcd_send_cmd(0x01);
    _delay_ms(2);
}