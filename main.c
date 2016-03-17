/*
 *LED library test
 *Created on: Mar 17, 2016
 *Author: Alttawab
 */


#include "HAL/LED.h"
#include "HAL/keyPad.h"
#include "HAL/SevenSegments.h"
#include <util\delay.h>
#include <avr/io.h>

int main()
{
	void_sevSeg_init() ;
		U16_t U16_i ;
		U16_t U16_temp;
		U16_i=0;
		U16_temp=0;
	while(1)
	{
		for(U16_i=999 ; U16_i>0 ; U16_i --)
			{
			int i;
			for(i=0; i<20 ; i++){
			void_sevSeg_dispaly( U16_i);
			}_delay_ms(1);
			}
	}
return (0);
}
