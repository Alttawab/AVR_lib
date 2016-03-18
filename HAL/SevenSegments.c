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

static U16_t U16_sevSeg_dispaly_digit(U16_t U16_numeric_value,  U8_t U8_digit ) ;

void void_sevSeg_init()
{
	S8_DIO_init_output_port_mask(SEVSEG_DATA_PORT ,0x0F );
	S8_DIO_init_output_port_mask(SEVSEG_ENABLE_PORT , 0x3C);
	S8_DIO_init_pin(SEVSEG_FLOAT_PORT  , SEVSEG_FLOAT_ENABLE ,HIGH);
	S8_DIO_set_port_mask(SEVSEG_ENABLE_PORT , 0x3C);
}


void void_sevSeg_dispaly( U16_t U16_numeric_value)
{
	if( U16_numeric_value > MAXIMUM_VALUE)
		U16_numeric_value = MAXIMUM_VALUE ;
	U16_numeric_value = U16_sevSeg_dispaly_digit(U16_numeric_value , SEVSEG_EN4);
	U16_numeric_value = U16_sevSeg_dispaly_digit(U16_numeric_value , SEVSEG_EN3);
	U16_numeric_value = U16_sevSeg_dispaly_digit(U16_numeric_value , SEVSEG_EN2);
	U16_numeric_value = U16_sevSeg_dispaly_digit(U16_numeric_value , SEVSEG_EN1);
}


static U16_t U16_sevSeg_dispaly_digit(U16_t U16_numeric_value,  U8_t U8_digit )
{
	S8_DIO_set_port_mask(SEVSEG_ENABLE_PORT , 0x3C);
	S8_DIO_clear_pin( SEVSEG_ENABLE_PORT , U8_digit);
	S8_DIO_clear_port_mask(SEVSEG_DATA_PORT , 0xF0);
	switch (U8_digit)
	{
	case SEVSEG_EN2:
		S8_DIO_set_port_mask(SEVSEG_DATA_PORT , U16_numeric_value /10 );
		U16_numeric_value %=10 ;
		break ;
	case SEVSEG_EN3:
		S8_DIO_set_port_mask(SEVSEG_DATA_PORT , U16_numeric_value /100 );
		U16_numeric_value %=100 ;
		break ;
	case SEVSEG_EN4:
		S8_DIO_set_port_mask(SEVSEG_DATA_PORT , U16_numeric_value /1000 );
		U16_numeric_value %=1000 ;
		break ;
	default :
		S8_DIO_set_port_mask(SEVSEG_DATA_PORT , U16_numeric_value  );
	}
	_delay_ms(DELAYS);
	return (U16_numeric_value);
}
