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

#define DATA_PORT 'C'
#define CONTROL_PORT 'B'
#define RS 0    /*CONTROL_PORT   RS=0 instruction mode RS=1 Data mode*/
#define RW 1	/*CONTROL_PORT   RW = 0 write mode , RW=1 read mode z*/
#define EN 2	/*CONTROL_PORT*/


void void_lcd_command(U8_t U8_command);
void void_lcd_data(U8_t U8_data);
void void_lcd_init();
void void_lcd_print(S8_t * S8_str);
void void_lcd_goto_xy(U8_t U8_x , U8_t U8_y);
void void_lcd_busy_flag();
void void_lcd_latch_data();
void void_reverse(S8_t * S8_str_ptr , U8_t U8_length);
void void_lcd_int_to_asci(S32_t S32_integer , S8_t * S8_str_ptr , U8_t U8_base);



#endif /* HAL_LCD_H_ */
