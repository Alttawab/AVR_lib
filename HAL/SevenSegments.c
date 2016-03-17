/*
 * SevenSegments.c
 *  Created on: Mar 17, 2016
 *      Author: Alttawab
 * this set for COMMON CATHOD seven segments
 * MCU DATA are connected to the display through the driver
 * 74ls47 active low encoder
 * 4 SevSeg used to display 4 digit 1 digit precision float .
 * all 4 SevSeg
 *
 *
 *
 *
 *
 *
 *
 */


#include "SevenSegments.h"
#include "../MCAL/D_IO.h"
#include <util\delay.h>





void void_sevSeg_init()
{
	S8_DIO_init_output_port_mask(SEVSEG_DATA_PORT ,0x0F );
	S8_DIO_init_output_port_mask(SEVSEG_ENABLE_PORT , 0x3C);
	S8_DIO_init_pin(SEVSEG_FLOAT_PORT  , SEVSEG_FLOAT_ENABLE ,HIGH);
	S8_DIO_set_port_mask(SEVSEG_ENABLE_PORT , 0x3C);
}



void void_sevSeg_dispaly(U16_t U16_numeric_value)
{


	S8_DIO_set_port_mask(SEVSEG_ENABLE_PORT , 0x3C);
	S8_DIO_clear_pin( SEVSEG_ENABLE_PORT , SEVSEG_EN4);
	S8_DIO_clear_port_mask(SEVSEG_DATA_PORT , 0xF0);
	S8_DIO_set_port_mask(SEVSEG_DATA_PORT , U16_numeric_value /1000 );
	U16_numeric_value %=1000 ;
	_delay_ms(DELAYS);

	S8_DIO_set_port_mask(SEVSEG_ENABLE_PORT , 0x3C);
	S8_DIO_clear_pin( SEVSEG_ENABLE_PORT , SEVSEG_EN3);
	S8_DIO_clear_port_mask(SEVSEG_DATA_PORT , 0xF0);
	S8_DIO_set_port_mask(SEVSEG_DATA_PORT , U16_numeric_value /100 );
	U16_numeric_value %=100 ;
	_delay_ms(DELAYS);

	S8_DIO_set_port_mask(SEVSEG_ENABLE_PORT , 0x3C);
	S8_DIO_clear_pin( SEVSEG_ENABLE_PORT , SEVSEG_EN2);
	S8_DIO_clear_port_mask(SEVSEG_DATA_PORT , 0xF0);
	S8_DIO_set_port_mask(SEVSEG_DATA_PORT , U16_numeric_value /10 );
	U16_numeric_value %=10 ;
	_delay_ms(DELAYS);

	S8_DIO_set_port_mask(SEVSEG_ENABLE_PORT , 0x3C);
	S8_DIO_clear_pin( SEVSEG_ENABLE_PORT , SEVSEG_EN1);
	S8_DIO_clear_port_mask(SEVSEG_DATA_PORT , 0xF0);
	S8_DIO_set_port_mask(SEVSEG_DATA_PORT , U16_numeric_value );
	_delay_ms(DELAYS);
	}


