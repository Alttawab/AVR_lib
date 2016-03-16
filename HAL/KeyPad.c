/*
* KeyPad.c
 *
 *  Created on: Mar 13, 2016
 *      Author: Alttawab
 */
#include "..\HAL\KeyPad.h"
#include "..\MCAL\D_IO.h"
#include <util/delay.h>
#include <avr/io.h>
#define KEYPAD_PORT 'A'
#define ROW1 4
#define ROW2 3
#define ROW3 2
#define COLUMN1 7
#define COLUMN2 6
#define COLUMN3 5

void delay(U8_t U8_time_in_ms)
{
	_delay_ms(U8_time_in_ms);
}
void void_keyPad_init()

{
	S8_DIO_init_output_port_mask(KEYPAD_PORT , 0x1C);
	S8_DIO_init_input_port_mask(KEYPAD_PORT , 0x1F);
	S8_DIO_set_port_mask(KEYPAD_PORT , 0xFC) ;
}


void void_keyPad_wait_keyRelease()
{
	S8_DIO_clear_port_mask(KEYPAD_PORT , 0xE3) ;
	do {
		do
		{
			delay(10);
		}  while( S16_DIO_read_port_mask(KEYPAD_PORT , 0x00E0) !=0x00E0);

	}  while( S16_DIO_read_port_mask(KEYPAD_PORT , 0x00E0) !=0x00E0);
}


void void_keyPad_wait_keyPress()
{
	do {
		S8_DIO_set_port_mask(KEYPAD_PORT , 0xFC) ;
		S8_DIO_clear_port_mask(KEYPAD_PORT , 0xE3);
		} while(S16_DIO_read_port_mask(KEYPAD_PORT , 0x00E0) == 0x00E0 );
}


U8_t U8_keyPad_scanKey()
{
	S16_t S16_keyDecode;
	U8_t U8_key;
	U8_key = 0 ;
	if(S16_DIO_read_port_mask(KEYPAD_PORT , 0x00FC) != 0x00E0)
	{
		        U8_t U8_scan_key ;
		        U8_scan_key= 0x0C  ;
		        U8_t U8_i;
		        for(U8_i=0x00; U8_i<=0x02; U8_i++)
		        {
		        	S8_DIO_set_port_mask(KEYPAD_PORT , 0xFC);
		        	S8_DIO_clear_pin(KEYPAD_PORT ,(4-U8_i) );
		        	S16_keyDecode=S16_DIO_read_port_mask(KEYPAD_PORT, 0x00E0);
		        	if(S16_keyDecode != 0x00E0)
		        		break ;
		        	U8_scan_key=(U8_scan_key>> 1)+0x10;
		        }

	        	S16_keyDecode=S16_keyDecode+(U8_scan_key & 0x1C) ;

	        	switch(S16_keyDecode)
	        	        {
	        	        case 0x006C:
	        	        	U8_key=1;
	        	        	break;
	        	        case 0x00AC:
	        	        	U8_key=2;
	        	        	break;
	        	        case 0x00CC:
	        	        	U8_key=3;
	        	        	break;
	        	        case 0x0074:
	        	        	U8_key=4;
	        	        	break;
	        	        case 0x00B4:
	        	        	U8_key=5;
	        	        	break;
	        	        case 0x00D4:
	        	        	U8_key=6;
	        	        	break;
	        	        case 0x0078:
	        	        	U8_key=7;
	        	        	break;
	        	        case 0x00B8:
	        	        	U8_key=8;
	        	        	break;
	        	        case 0x00D8:
	        	        	U8_key=9;
	        	        	break;
	        	        default :
	        	        	U8_key=10;
	        	        }
	        }
	return (U8_key);
}
