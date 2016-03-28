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
#include <stdlib.h>
#include "MCAL\ADC.h"
int main()
{
void_lcd_init();
void_adc_init('A' , 1);
U16_t U16_value ;
U16_value=0;
char  char_temp[7] ={'\0'};
FP64 FP64_num;
FP64_num =0.0;
while (1)
{
		U16_value=U16_adc_read();

		itoa(U16_value ,char_temp ,10);
		void_lcd_goto_xy(1,1);
		void_lcd_print((S8_t * )"ADC code:");
		void_lcd_goto_xy(10,1);
		void_lcd_print((S8_t * )char_temp);
		void_lcd_print((S8_t * )"   ");

		FP64_num=4.882 /1024 ;
		FP64_num=FP64_num * U16_value ;
		FP64_num*=100;
		dtostrf(FP64_num ,4,1,char_temp);
		void_lcd_goto_xy(1,2);
		void_lcd_print((S8_t * )"Temp:");
		void_lcd_goto_xy(6,2);
		void_lcd_print((S8_t * )char_temp);
		void_lcd_data(0xDF);	/* ° symbol*/
		_delay_ms(500);
	}
}
