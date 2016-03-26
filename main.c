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
#define SET_PIN(PORT , PIN) PORT |= (1<<PIN)
#define RESET_PIN(PORT , PIN ) PORT &= ~(1<<PIN)



int main()

{
	void_lcd_init();
	S8_t * S8_arr_keyScan =(S8_t *)"\0";
	void_keyPad_init();
	while(1)
	{
	 void_lcd_int_to_asci( -57855 , S8_arr_keyScan , 10);

	//void_keyPad_wait_keyRelease();
//	void_keyPad_wait_keyPress();
//	S8_arr_keyScan[0] =(S8_t)U8_keyPad_scanKey()+48;

	void_lcd_print(S8_arr_keyScan);

	}


}
