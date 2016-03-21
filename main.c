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

#define SET_PIN(PORT , PIN) PORT |= (1<<PIN)
#define RESET_PIN(PORT , PIN ) PORT &= ~(1<<PIN)



int main()

{
	void_keyPad_init();
	void_lcd_init();
	S8_t S8_arr_keyScan [2] = {0 , '\0'}; ;
	while(1)
	{
	void_keyPad_wait_keyRelease();
	void_keyPad_wait_keyPress();
	S8_arr_keyScan[0] =(S8_t)U8_keyPad_scanKey()+48;
	void_lcd_print(S8_arr_keyScan);

	}
	return (0);
}

