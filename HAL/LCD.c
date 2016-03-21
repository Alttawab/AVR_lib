#include"LCD.h"



void void_lcd_command(U8_t U8_command)
{
	S8_DIO_write_port(DATA_PORT  , U8_command);
	S8_DIO_clear_pin( CONTROL_PORT , RS);
	S8_DIO_clear_pin( CONTROL_PORT , RW);
	S8_DIO_set_pin( CONTROL_PORT , EN) ;
	_delay_us(1);
	S8_DIO_clear_pin( CONTROL_PORT , EN) ;
	_delay_us(100);
}


void void_lcd_data(U8_t U8_data)

 {
	S8_DIO_write_port(DATA_PORT, U8_data);
	S8_DIO_set_pin( CONTROL_PORT, RS);
	S8_DIO_clear_pin( CONTROL_PORT, RW);
	S8_DIO_set_pin( CONTROL_PORT, EN);
	_delay_us(1);
	S8_DIO_clear_pin( CONTROL_PORT, EN);
	_delay_us(100);
}



void void_lcd_init()
{

	S8_DIO_init_port(DATA_PORT, 0xFF);
	S8_DIO_init_port(CONTROL_PORT, 0xFF);
	S8_DIO_clear_pin(CONTROL_PORT, EN);
	_delay_us(2000);
	void_lcd_command(0x3C);
	void_lcd_command(0x0F);
	void_lcd_command(0x01);
	_delay_us(2000);
	void_lcd_command(0x06);
}


void void_lcd_print(S8_t * S8_str)
{
	U8_t U8_i = 0;
	while( (S8_str [U8_i]) !=0)
	{
		void_lcd_data((S8_str[U8_i]));
		  U8_i++ ;
	}

}

void void_lcd_goto_xy(U8_t U8_x , U8_t U8_y)
{
	switch ( U8_y)
	{
		case 1:
			if(U8_x <=16 && U8_x >=1)
			{
				void_lcd_command(0x80 +(U8_x - 1 ));
			}
			else
				void_lcd_command(0x8F);
			break ;
		case 2:
			if(U8_x <=16 && U8_x >=1)
			{
			void_lcd_command(0xC0 +(U8_x -1) );
			}
			else
				void_lcd_command(0xCF);
			break ;
		default :
		void_lcd_command(0x80);
	}
}
