#include"LCD.h"

void void_lcd_command(U8_t U8_command)
{
	_delay_us(1);
	void_lcd_busy_flag() ;
	S8_DIO_write_port(DATA_PORT  , U8_command);
	S8_DIO_clear_pin( CONTROL_PORT , RS);
	S8_DIO_clear_pin( CONTROL_PORT , RW);
	void_lcd_latch_data();

}


void void_lcd_data(U8_t U8_data)

 {
	void_lcd_busy_flag() ;
	S8_DIO_write_port(DATA_PORT, U8_data);
	S8_DIO_set_pin( CONTROL_PORT, RS);
	S8_DIO_clear_pin( CONTROL_PORT, RW);
	void_lcd_latch_data();
}



void void_lcd_init()

{

	S8_DIO_init_output_port_mask(DATA_PORT , 0xFF );
	S8_DIO_init_output_port_mask(CONTROL_PORT , 0x07 );
	S8_DIO_clear_pin(CONTROL_PORT , EN);
	void_lcd_command(0x3C);
	void_lcd_command(0x0F);
	void_lcd_command(0x01);
	_delay_us(1700);
	void_lcd_command(0x06);
}


void void_lcd_print(S8_t * S8_str)
{
	U8_t U8_i = 0;
	while( (S8_str [U8_i]) !=0)
	{
		void_lcd_data((S8_str[U8_i]));
		  U8_i++ ;
		  _delay_us(1000);
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

void void_lcd_busy_flag()  /*1 wait while lcd  is busy */
{
	S8_DIO_init_input_port_mask(DATA_PORT , 0x00 );  /*make data port in input mode "read"*/
	S8_DIO_clear_pin(CONTROL_PORT , RS);
	S8_DIO_set_pin(CONTROL_PORT , RW);

	do
	{
		void_lcd_latch_data() ;

	}while (S16_DIO_read_port_mask(DATA_PORT , 0xFF)<=0x80);

	S8_DIO_init_output_port_mask(DATA_PORT , 0xFF ); /*make data port in output mode "Write"*/

}

/*latch function*/
void void_lcd_latch_data()
{
	S8_DIO_set_pin(CONTROL_PORT  , EN);
	asm volatile ("nop");
	asm volatile ("nop");
	S8_DIO_clear_pin(CONTROL_PORT , EN);

}

	/*write intger to string function*/
void void_lcd_int_to_asci(S32_t S32_integer , S8_t * S8_str_ptr , U8_t U8_base)
{
	U8_t U8_i ;
	U8_i =0 ;
	bool bool_sign ;
	bool_sign =FALSE ;
	if(S32_integer <0)
	{
		S32_integer *= -1 ;
		bool_sign = TRUE ;
	}
	if(S32_integer == 0 )
	{
		*(S8_str_ptr+U8_i)='0' ;
				U8_i += 1;
		*(S8_str_ptr+U8_i)='\0';

	}

	else
	{
		do
		{
		U8_t	U8_rem ;
		U8_rem = S32_integer %	U8_base ;
		*(S8_str_ptr+U8_i)=(U8_rem > 10)? (U8_rem -10)+'A' :U8_rem+'0' ;
		S32_integer /= U8_base;
		U8_i += 1;
		}while(S32_integer != 0);
		if(bool_sign && U8_base == 10)
		{
			*(S8_str_ptr + U8_i) = '-' ;
			U8_i += 1;
			*(S8_str_ptr + U8_i) = '\0' ;
		}
	}
	void_reverse(S8_str_ptr , U8_i-1) ;

}
	void void_reverse(S8_t * S8_str_ptr , U8_t U8_length)

	{
		U8_t U8_i ;
		U8_i = 0 ;

		S8_t S8_temp ;
		while(U8_i < (U8_length/2) )
         {
		S8_temp= *(S8_str_ptr + U8_i) ;
		*(S8_str_ptr + U8_i) = *((S8_str_ptr + U8_length )- U8_i) ;
		*((S8_str_ptr + U8_length )-U8_i) =   S8_temp ;
		U8_i =U8_i+1;
         }
	}


/******basic fuction******/

	/*1_return home function */
	/*add clear display function*/
	/*blink crusor function on /off */
	/*display light off power saver*/

/****Intermediate functions*****/

	/*function mode 1 line or 2 line and 4bit or 8 bit etc*/
	/*write double function*/
	/*rotate line */
	/*shift line */
	/*move line*/

/******advnced function******/

	/*menu functions*/
	/*draw any symbol*/
