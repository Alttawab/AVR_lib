#include"LCD.h"

#define FOUR_BIT_MODE /*lower nibble is grounded*/
#define RW_DISABLE   /*RW is grounded to be always in write mode*/
#define ON 1
#define OFF 0
#define DATA_PORT 'B'
#define CONTROL_PORT 'C'
#define RS 6    /*CONTROL_PORT   RS=0 instruction mode RS=1 Data mode*/
#define EN 7	/*CONTROL_PORT*/
#ifndef RW_DISABLE
#define RW 5	/*CONTROL_PORT   RW = 0 write mode , RW=1 read mode z*/
#endif


#ifndef FOUR_BIT_MODE
	#define PORT_DDR_MASK 0xFF /* output all port*/
#endif //FOUR_BIT_MODE

#ifdef FOUR_BIT_MODE
	#define PORT_DDR_MASK 0xF0 /*Output the higher nibble port*/
#endif //FOUR_BIT_MODE





void void_lcd_init()
{
	_delay_us(15000);

	S8_DIO_init_output_port_mask(DATA_PORT ,PORT_DDR_MASK );/*DATA port output is output*/
	S8_DIO_init_output_port_mask(CONTROL_PORT , 0xC0 );/*control port output is output*/

/*#ifdef FOUR_BIT_MODE
	S8_DIO_clear_pin( CONTROL_PORT , RS);

	#ifndef RW_DISABLE
		S8_DIO_clear_pin( CONTROL_PORT , RW);
	#endif

	S8_DIO_set_port_mask(DATA_PORT ,  0x20);
	void_lcd_latch_data();

#endif
*/
	void_lcd_command(0x22);
	void_lcd_function_set(HIGH , LOW);/*Function set to   number of lines = 2 and fontsize 5*8 */
	void_lcd_display_control(ON ,ON ,OFF);/*Display on and cursor on  and cursor position off*/
	void_lcd_clear_display();	/*clear display command 0x01*/
	void_lcd_entry_mode_set(LOW ,HIGH); /* cursor move right*/
	_delay_us(10000);

}









void void_lcd_command(U8_t U8_command)
{
#ifndef RW_DISABLE
	void_lcd_busy_flag() ;
	S8_DIO_clear_pin( CONTROL_PORT , RW);
#endif
#ifdef RW_DISABLE
	_delay_us(2);
#endif



#ifdef FOUR_BIT_MODE
	S8_DIO_clear_pin( CONTROL_PORT , RS);

	S8_DIO_clear_port_mask(DATA_PORT  , 0x0F); //clear the higher nibble to be ready to receive a new nibble
	S8_DIO_set_port_mask(DATA_PORT , U8_command & 0xF0);
	void_lcd_latch_data();

	U8_command =U8_command <<  4 ;
	S8_DIO_clear_port_mask(DATA_PORT  , 0x0F); //clear the higher nibble to be ready to receive a new nibble
	S8_DIO_set_port_mask(DATA_PORT , U8_command & 0xF0);
	void_lcd_latch_data();

#endif //FOUR_BIT_MODE



#ifndef FOUR_BIT_MODE
	void_lcd_busy_flag() ;
	S8_DIO_write_port(DATA_PORT  , U8_command);
	S8_DIO_clear_pin( CONTROL_PORT , RS);
	S8_DIO_clear_pin( CONTROL_PORT , RW);
	void_lcd_latch_data();
#endif //FOUR_BIT_MODE
	_delay_us(100);
}







void void_lcd_data(U8_t U8_data)
 {
#ifndef RW_DISABLE
	void_lcd_busy_flag() ;
	S8_DIO_clear_pin( CONTROL_PORT, RW);
#endif
#ifdef RW_DISABLE
	_delay_us(2);
#endif

	S8_DIO_set_pin( CONTROL_PORT, RS);

#ifdef FOUR_BIT_MODE
	S8_DIO_clear_port_mask(DATA_PORT  , 0x0F); //clear the higher nibble to be ready to receive a new nibble
	S8_DIO_set_port_mask(DATA_PORT , U8_data & 0xF0);
	void_lcd_latch_data();

	U8_data = U8_data << 4 ;
	S8_DIO_clear_port_mask(DATA_PORT  , 0x0F); //clear the higher nibble to be ready to receive a new nibble
	S8_DIO_set_port_mask(DATA_PORT , U8_data & 0xF0);
	void_lcd_latch_data();
#endif //FOUR_BIT_MODE

#ifndef FOUR_BIT_MODE
	S8_DIO_write_port(DATA_PORT, U8_data);
	void_lcd_latch_data();
#endif //FOUR_BIT_MODE
	_delay_us(100);
}









void void_lcd_print(S8_t * S8_str)
{
	U8_t U8_i = 0;
	while( (S8_str [U8_i]))
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









#ifndef RW_DISABLE
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
#endif









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








	/*1_return home function */

void void_lcd_return_home()
	{
		void_lcd_command(0x02);
		_delay_us(1700);

	}








	/*add clear display function*/
void void_lcd_clear_display()
	{
		void_lcd_command(0x01);
		_delay_us(1700);
	}







	/*turn on display turn on cursor blink cursor function on /off */
void void_lcd_display_control(U8_t U8_display_control_ON_OR_OFF ,U8_t U8_cursor_control_ON_OR_OFF,U8_t U8_curseor_blink_control_ON_OR_OFF  )
	{
		if(((U8_display_control_ON_OR_OFF | U8_cursor_control_ON_OR_OFF |U8_curseor_blink_control_ON_OR_OFF) == 0 )||(( U8_display_control_ON_OR_OFF |U8_cursor_control_ON_OR_OFF | U8_curseor_blink_control_ON_OR_OFF) == 1))
			void_lcd_command(0x08 | (U8_display_control_ON_OR_OFF<<2) | (U8_cursor_control_ON_OR_OFF<<1) | (U8_curseor_blink_control_ON_OR_OFF));
		else
			void_lcd_command(0x08);
		_delay_us(100);
	}










void void_lcd_function_set( U8_t U8_display_number_lines_HIGH_2_line_and_LOW_1_line , U8_t U8_display_font_HIGH_5x11_and_LOW_5x8)
{
if(((U8_display_number_lines_HIGH_2_line_and_LOW_1_line | U8_display_font_HIGH_5x11_and_LOW_5x8 ) == 0)||((U8_display_number_lines_HIGH_2_line_and_LOW_1_line | U8_display_font_HIGH_5x11_and_LOW_5x8 ) == 1))
{
#ifndef FOUR_BIT_MODE
		void_lcd_command(0x30 | (U8_display_number_lines_HIGH_2_line_and_LOW_1_line<<3) | (U8_display_font_HIGH_5x11_and_LOW_5x8<<2));
#endif
#ifdef FOUR_BIT_MODE
		void_lcd_command(0x20 | (U8_display_number_lines_HIGH_2_line_and_LOW_1_line<<3) | (U8_display_font_HIGH_5x11_and_LOW_5x8<<2));
#endif
}
else
	{
#ifndef FOUR_BIT_MODE
	void_lcd_command(0x30);
#endif
#ifdef FOUR_BIT_MODE
	void_lcd_command(0x20);
#endif
	}
_delay_us(100);
}









void void_lcd_entry_mode_set( U8_t U8_select_to_move_display_High_and_cursor_LOW , U8_t  U8_cursorORdisplay_move_right_HIGH_and_left_LOW)

{

	if(((U8_select_to_move_display_High_and_cursor_LOW | U8_cursorORdisplay_move_right_HIGH_and_left_LOW )==0)||((U8_select_to_move_display_High_and_cursor_LOW | U8_cursorORdisplay_move_right_HIGH_and_left_LOW) ==1 ) )
		void_lcd_command(0x04 | (U8_select_to_move_display_High_and_cursor_LOW  ) | (U8_cursorORdisplay_move_right_HIGH_and_left_LOW << 1));
	else
		void_lcd_command(0x04);
	_delay_us(100);
}






/******basic fuction******/

/****Intermediate functions*****/

	/*todo :write double function*/



/******advnced function******/
	/*todo:menu functions*/
	/*todo:draw any symbol*/

