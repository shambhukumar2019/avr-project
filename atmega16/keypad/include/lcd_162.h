/**
 * @file lcd_162.h
 * @author shambhu kumar (you@domain.com)
 * @brief lcd device driver header file
 * @version 0.1
 * @date 2024-03-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _LCD_162_H_
#define _LCD_162_H_


#include "common.h"



#define LCD_DDR         DDRC
#define LCD_PORT        PORTC
#define LCD_CRTL_PORT   PORTD

#define LCD_EN_PIN      PD7
#define LCD_RS_PIN      PD6

#define LCD_CMD_MODE    CLEAR_BIT(LCD_CRTL_PORT,LCD_RS_PIN)
#define LCD_DATA_MODE   SET_BIT(LCD_CRTL_PORT,LCD_RS_PIN)


#define LCD_ENABLE_PULSE    {SET_BIT(LCD_CRTL_PORT,LCD_EN_PIN);\
                            _delay_us(2);\
                            CLEAR_BIT(LCD_CRTL_PORT,LCD_EN_PIN);}


void lcd_send_cmd(uint8_t);

void lcd_send_data(uint8_t);

void lcd_init(void);

void lcd_send_enable_pulse(void);

void lcd_send_word(uint8_t*);

void lcd_cursor_pos(uint8_t,uint8_t);

void lcd_clear_disp(void);



#endif