/*
 *LED library test
 *Created on: Mar 17, 2016
 *Author: Alttawab
 */


#include "HAL\LED.h"
#include <util/delay.h>

void delay();
int main()
{
	void_led_init_all_led();
	void_led_all_led_off();
	while(1)
	{
		delay();
		void_led_1_on();
		delay();
		void_led_1_off();
		delay();
		void_led_2_on();
		delay();
		void_led_2_off();
		delay();
		void_led_3_on();
		delay();
		void_led_3_off();
		delay();
		void_led_4_on();
		delay();
		void_led_4_off();
		delay();
		void_led_all_led_on();
		delay();
		void_led_all_led_off();

	}
}

void delay()
{
	_delay_ms(1000);
}
