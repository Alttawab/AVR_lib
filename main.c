/*
 *LED library test
 *Created on: Mar 17, 2016
 *Author: Alttawab
 */


#include "HAL/LED.h"
#include "HAL/keyPad.h"
#include <util\delay.h>
int main()
{
	void_led_init_all_led();
	void_keyPad_init();
	void_led_all_led_off();
	U8_t U8_key ;
	U8_key=0;
	while(1)
	{
		void_keyPad_wait_keyRelease();
		void_keyPad_wait_keyPress();
		U8_key =U8_keyPad_scanKey();

		switch(U8_key)


		{
		case 1:
			void_led_all_led_off();
			void_led_1_on();
			break ;
		case 2:
			void_led_all_led_off();
			void_led_2_on();
			break ;
		case 3:
			void_led_all_led_off();
			void_led_1_on();
			void_led_2_on();
			break ;
		case 4 :
			void_led_all_led_off();
			void_led_3_on();
			break ;
		case 5:
			void_led_all_led_off();
			void_led_3_on();
			void_led_1_on();
			break ;
		case 6:
			void_led_all_led_off();
			void_led_3_on();
			void_led_2_on();
			break ;
		case 7:
			void_led_all_led_off();
			void_led_1_on();
			void_led_2_on();
			void_led_3_on();
			break ;
		case 8:
			void_led_all_led_off();
			void_led_4_on();
			break ;
		case 9:
			void_led_all_led_off();
			void_led_1_on();
			void_led_4_on();
			break ;
		default :
			void_led_all_led_off();
			void_led_4_on();
			void_led_2_on();
		}

	}

return (0);
}
