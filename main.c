/*
 *LED library test
 *Created on: Mar 17, 2016
 *Author: Alttawab
 */

#include "HAL/LED.h"
#include "HAL/keyPad.h"
#include "HAL/SevenSegments.h"
#include <util\delay.h>
#define DELAY 10

U16_t U16_pow(U16_t U16_num , U8_t U8_power);

int main() {
	void_sevSeg_init();
	void_keyPad_init();
	void_keyPad_wait_keyRelease();
	U16_t U16_num;
	U8_t U8_ten_order ;
	U8_t U8_i ;
	     U16_num = 0;
		 U8_ten_order =0 ;
		 U8_i= 0;
	while (1)
	{


		if(bool_keyPad_wait_keyPress_open(50))
		{
			U16_num =(U16_num * U16_pow(10,U8_ten_order)) + U8_keyPad_scanKey() ;
			U8_ten_order ++ ;
		}
			for (U8_i = 0; U8_i < (3* DELAY); U8_i++)
				{
				void_sevSeg_dispaly(U16_num);

				}
			_delay_ms(DELAY);

	}
	return (0);
}

U16_t U16_pow(U16_t U16_num , U8_t U8_power)
{
	U8_t U8_i ;
	for(U8_i=1 ;U8_i < U8_power ; U8_i ++ )
	{
		if(U8_power == 0)
			U16_num =1 ;
			break ;
		if(U8_power == 1)
			U16_num *=1 ;
			break ;
		U16_num *= U16_num ;
	}
	return (U16_num);
}


