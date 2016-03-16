#include"..\HAL\LED.h"
#include "..\MCAL\D_IO.h"


/*Init*/
void void_led_init_all_led()
{
    S8_DIO_init_output_port_mask(LED_PORT,0xF0);
}

void void_led_init_led_1()
{
    S8_DIO_init_pin(LED_PORT , LED1 ,OUTPUT);
}

void void_led_init_led_2()
{
    S8_DIO_init_pin(LED_PORT , LED2 ,OUTPUT);
}
void void_led_init_led_3()
{
    S8_DIO_init_pin(LED_PORT , LED3 ,OUTPUT);
}
void void_led_init_led_4()
{
    S8_DIO_init_pin(LED_PORT , LED4 ,OUTPUT);
}

/*ON*/
void  void_led_all_led_off()
{
    S8_DIO_set_port_mask(LED_PORT , 0xF0) ;
}

void void_led_1_off()
{
    S8_DIO_set_pin(LED_PORT , LED1) ;


}
void void_led_2_off()
{
    S8_DIO_set_pin(LED_PORT , LED2) ;


}
void void_led_3_off()
{
    S8_DIO_set_pin(LED_PORT , LED3) ;


}
void void_led_4_off()
{
    S8_DIO_set_pin(LED_PORT , LED4) ;


}
/*off*/
void void_led_all_led_on()
{
    S8_DIO_clear_port_mask(LED_PORT , 0x0F) ;
}

void void_led_1_on()
{
    S8_DIO_clear_pin(LED_PORT , LED1) ;


}

void void_led_2_on()
{
    S8_DIO_clear_pin(LED_PORT , LED2) ;


}


void void_led_3_on()
{
    S8_DIO_clear_pin(LED_PORT , LED3) ;


}


void void_led_4_on()
{
    S8_DIO_clear_pin(LED_PORT , LED4) ;

}

void void_led_off(U8_t LedNumber)
{
	switch (LedNumber)
	{
		case 1:S8_DIO_set_pin(LED_PORT , LED1) ; break ;
		case 2:S8_DIO_set_pin(LED_PORT , LED2) ; break ;
		case 3:S8_DIO_set_pin(LED_PORT , LED3) ; break ;
		case 4:S8_DIO_set_pin(LED_PORT , LED4) ; break ;
		default:
			break;
	}
}


void void_led_on(U8_t LedNumber)
{
	switch (LedNumber)
	{
		case 1: S8_DIO_clear_pin(LED_PORT , LED1) ; break ;
		case 2: S8_DIO_clear_pin(LED_PORT , LED2) ; break ;
		case 3: S8_DIO_clear_pin(LED_PORT , LED3) ; break ;
		case 4: S8_DIO_clear_pin(LED_PORT , LED4) ; break ;
		default :
			break ;

	}
}

