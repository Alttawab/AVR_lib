/*
 *LED library test
 *Created on: Mar 17, 2016
 *Author: Alttawab
 */

#include "HAL/LED.h"
#include "HAL/keyPad.h"
#include "HAL/SevenSegments.h"
#include <util\delay.h>
#include "MCAL\D_IO.h"
#include "HAL\LCD.h"
#include "serviceLayer\stdTypes.h"
int main()

{
	void_lcd_init();
	void_keyPad_init();
	S8_t  S8_arr_keyScan[10] ={'\0'};
	U8_t U8_num ;
	U8_num = 0;
	while(1)
	{
	void_keyPad_wait_keyRelease();
	void_keyPad_wait_keyPress();
	U8_num = U8_keyPad_scanKey() ;

	void_lcd_goto_xy(1 , 1);
	void_lcd_print((S8_t *)"DEC=");
	void_lcd_int_to_asci(U8_num, S8_arr_keyScan , 10);
	void_lcd_goto_xy(5 , 1) ;
	void_lcd_print(S8_arr_keyScan);

	void_lcd_goto_xy(1 , 2) ;
	void_lcd_print((S8_t *)"HEX=");
	void_lcd_goto_xy(5 , 2) ;
	void_lcd_int_to_asci(U8_num, S8_arr_keyScan , 16);
	void_lcd_print(S8_arr_keyScan);

	}

}
