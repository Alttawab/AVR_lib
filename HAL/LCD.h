/*
 * LCD.h
 *
 *  Created on: Mar 21, 2016
 *      Author: Alttawab
 */

#ifndef HAL_LCD_H_
#define HAL_LCD_H_
#include "..\ServiceLayer\stdTypes.h"
#include "..\MCAL\D_IO.h"
#include "util/delay.h"



void void_lcd_command(U8_t U8_command);
void void_lcd_data(U8_t U8_data);
void void_lcd_init();
void void_lcd_print(S8_t * S8_str);
void void_lcd_goto_xy(U8_t U8_x , U8_t U8_y);
void void_lcd_busy_flag();
void void_lcd_latch_data();
void void_reverse(S8_t * S8_str_ptr , U8_t U8_length);
void void_lcd_int_to_asci(S32_t S32_integer , S8_t * S8_str_ptr , U8_t U8_base);
void void_lcd_return_home() ;
void void_lcd_clear_display();
void void_lcd_display_control(U8_t U8_display_control_ON_OR_OFF ,U8_t U8_cursor_control_ON_OR_OFF,U8_t U8_curseor_blink_control_ON_OR_OFF  );
void void_lcd_function_set( U8_t U8_display_number_lines_HIGH_2_line_and_LOW_1_line , U8_t U8_display_font_HIGH_5x11_and_LOW_5x8);
void void_lcd_entry_mode_set( U8_t U8_select_to_move_display_High_and_cursor_LOW , U8_t U8_cursorORdisplay_move_right_HIGH_and_left_LOW) ;


#endif /* HAL_LCD_H_ */
