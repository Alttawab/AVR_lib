/*
 * ADC.c
 *
 *  Created on: Mar 26, 2016
 *      Author: Alttawab
 */
#include "D_IO.h"
#include "adc.h"

/*ADC SETUP*/
//#define FREQUANCY_PRE_SCALER 2  /*Recommended to use this macros if differntial_mode activated  Uncomment if user need specific prescaler */
#define ADC_REFERNCE_VOLTAGE 'A'

/*ADCSRA*/
#define ADEN 	7
#define ADSC	6
#define ADATE	5
#define ADIF	4
#define ADIE	3
#define ADPS2	2
#define ADPS1	1
#define ADPS0	0

/*ADMUX REGISTER*/
#define ADREF1 	7
#define ADREF0 	6
#define ADLAR 	5
#define ADMUX4	4
#define ADMUX3	3
#define ADMUX2	2
#define ADMUX1	1
#define ADMUX0	0


void void_adc_init_single_ended_input(U8_t U8_port ,U8_t U8_pin )
{
	S8_DIO_init_pin(U8_port ,U8_pin,INPUT); 		/*make pin input */
	void_adc_enable(SET);							/*Enable the ADC*/
	void void_adc_prescaler_setup();				/*select the prescaler*/
	adc_select_refrence(ADC_REFERNCE_VOLTAGE);						/*select reference to be Avref */
	CLEAR_PIN(ADMUX , ADLAR);
	CLEAR_PIN(ADMUX , ADMUX0);						/*						  A0*/
	CLEAR_PIN(ADMUX , ADMUX2);						/*			analoge			*/
	CLEAR_PIN(ADMUX , ADMUX1);						/*					channel	*/
	if(U8_pin<8)
	ADMUX|=U8_pin;
	CLEAR_PIN(ADMUX , ADMUX3);						/*		the					*/
	CLEAR_PIN(ADMUX , ADMUX4);						/*Select					*/
}


/*read pin*/
U16_t U16_adc_read_single_ended_input()
{
	U8_t U8_analoge_data_low ;
	U8_t U8_analoge_data_high;
	U16_t U16_value ;
	U8_analoge_data_low =0 ;
	U8_analoge_data_high=0;
	U16_value =0;
	SET_PIN(ADCSRA , ADSC);					/*start conversion*/
	while(!(1<<ADIF)&(ADCSRA));				/*wait until interrupt flag to be 1*/
	SET_PIN(ADCSRA , ADIF);					/* clear interrupt flag by sit the bit*/
	U8_analoge_data_low = ADCL ;
	U8_analoge_data_high = ADCH ;
	U16_value = (((U16_t )U8_analoge_data_high)<<8) +U8_analoge_data_low ;
	return (U16_value) ;
}


/*read pin in differtial mode */
/*range from 0x200 (-512) to 0x1FF(511)
 * */
S16_t S16_adc_read_differential_input()
{
	U8_t U8_analog_data_low ;
	U8_t U8_analog_data_high;
	S16_t S16_value ;

	U8_analog_data_low =0 ;
	U8_analog_data_high=0 ;
	S16_value =0;
	SET_PIN(ADCSRA , ADSC);				/*start conversion*/
	while(!(1<<ADIF)&(ADCSRA));
	SET_PIN(ADCSRA , ADIF);					/* clear interrupt flag by sit the bit*/
	U8_analog_data_low = ADCL ;
	U8_analog_data_high = ADCH ;
	if(U8_analog_data_high |=(1<<1))
	{
		U8_analog_data_high |=(1<<2);
		U8_analog_data_high |=(1<<3);
		U8_analog_data_high |=(1<<4);
		U8_analog_data_high |=(1<<5);
		U8_analog_data_high |=(1<<6);
		U8_analog_data_high |=(1<<7);
	}

	S16_value = (((U16_t )U8_analog_data_high)<<8) +U8_analog_data_low ;
	return (S16_value) ;
}



/*Enable ADC */
void void_adc_enable(U8_t U8_state)
{
	switch(U8_state)
	{
	case 1:
		ADCSRA |=(1<<ADEN);
		break ;
	default :
		ADCSRA &=~(1<<ADEN);
	}
}




/*void_adc_prescaler_setup function provide autosetup and manual adjacent the prescaler
 * #define FREQUANCY_PRE_SCALER - prescaler -  prescaler should be selected between (2,4,8,16,32,64,128)
 * and should be value in this range the F_CPU / ( 50 to 200) KHz as mentioned in the datasheet.   */
void void_adc_prescaler_setup()
{
#ifndef FREQUANCY_PRE_SCALER
	U8_t U8_frequancy_prescaler =F_CPU /200000;
	U8_t U8_i;

	U8_i = 128 ;
		while(!(U8_frequancy_prescaler /U8_i))
		{
			U8_i /= 2 ;
		}
		U8_frequancy_prescaler=U8_i;
	switch(U8_frequancy_prescaler)
#endif

#ifdef FREQUANCY_PRE_SCALER
	switch(FREQUANCY_PRE_SCALER)
#endif
	{
	case 2:
		SET_PIN(ADCSRA , ADPS0);
		CLEAR_PIN(ADCSRA , ADPS1);
		CLEAR_PIN(ADCSRA , ADPS2);
		break;
	case 4:
		CLEAR_PIN(ADCSRA , ADPS0);
		SET_PIN(ADCSRA , ADPS1);
		CLEAR_PIN(ADCSRA , ADPS2);
		break;
	case 8:
		SET_PIN(ADCSRA , ADPS0);
		SET_PIN(ADCSRA , ADPS1);
		CLEAR_PIN(ADCSRA , ADPS2);
		break;
	case 16:
		CLEAR_PIN(ADCSRA , ADPS0);
		CLEAR_PIN(ADCSRA , ADPS1);
		SET_PIN(ADCSRA , ADPS2);
		break;
	case 32:
		SET_PIN(ADCSRA , ADPS0);
		CLEAR_PIN(ADCSRA , ADPS1);
		SET_PIN(ADCSRA , ADPS2);
		break;
	case 64:
		CLEAR_PIN(ADCSRA , ADPS0);
		SET_PIN(ADCSRA , ADPS1);
		SET_PIN(ADCSRA , ADPS2);
		break;
	case 128:
		SET_PIN(ADCSRA , ADPS0);
		SET_PIN(ADCSRA , ADPS1);
		SET_PIN(ADCSRA , ADPS2);
		break;
	default:
		CLEAR_PIN(ADCSRA , ADPS0);
		CLEAR_PIN(ADCSRA , ADPS1);
		CLEAR_PIN(ADCSRA , ADPS2);
	}
}





/*Select reference provid choise from 3 refernce
 * A=AREF
 * V=AVCC (make sure that there isn't constant voltage in AREF pin)
 * m=2.56v internal voltage reference (make sure that there isn't constant voltage in AREF bin) */
void adc_select_refrence(U8_t U8_Aref_or_aVcc_or_Internal_2v56_ref)
{

	switch(U8_Aref_or_aVcc_or_Internal_2v56_ref)
	{
		case 'A':
		case 'a':
			CLEAR_PIN(ADMUX , ADREF1);
			CLEAR_PIN(ADMUX , ADREF0);		/*Select AREF as  REFERANCE	*/
			break ;
		case 'V':
		case 'v':
			CLEAR_PIN(ADMUX , ADREF1);		/* SELECT voltage supply	 */
			SET_PIN(ADMUX , ADREF0);		/*			as	 a REFERANCE */
			break ;
		case 'I':
		case 'i':
			SET_PIN(ADMUX , ADREF1);		/* SELECT internal 			*/
			SET_PIN(ADMUX , ADREF0);		/*				  REFERANCE	*/
			break ;

		default :

			CLEAR_PIN(ADMUX , ADREF1);		/* default AREF as			*/
			CLEAR_PIN(ADMUX , ADREF0);		/*				  REFERANCE	*/
	}
}


/*differential input mode  select one from this choices
 *	1x 		gain (positive , negative)(0,1)(1,1)(2,1)(3,1)(4,1)(5,1)(6,1)(7,1)(0,2)(1,2)(2,2)(3,2)(4,2)(5,2)
 *	10x		gain (POSITIVE , negative)(0,0)(1,0)(2,2)(2,3)
 *	200x	gain (POSITIVE , negative)(0,0)(1,0)(2,2)(2,3)*/

void void_adc_init_differential_input (U8_t U8_port , U8_t U8_positive_differential, U8_t U8_negative_differential , U8_t U8_gain)
{
	S8_DIO_init_pin(U8_port ,U8_positive_differential,INPUT); 		/*make pin input */
	S8_DIO_init_pin(U8_port ,U8_negative_differential,INPUT); 		/*make pin input */
	void_adc_enable(SET);							/*Enable the ADC*/
	void void_adc_prescaler_setup();				/*select the prescaler*/
	CLEAR_PIN(ADMUX , ADLAR);						/*select right LSP to store data*/
	adc_select_refrence(ADC_REFERNCE_VOLTAGE);						/*select reference to be Avref */

	switch (U8_gain)
	{
//case 10x gain
			case 10:
				CLEAR_PIN(ADMUX , ADMUX4);
				SET_PIN(ADMUX , ADMUX3);
				CLEAR_PIN(ADMUX , ADMUX1);
				switch(U8_negative_differential)
				{
					case 2:
						switch(U8_positive_differential)
						{
							case 3:
								SET_PIN(ADMUX , ADMUX2);
								SET_PIN(ADMUX , ADMUX0);
								break;
							default:
								SET_PIN(ADMUX , ADMUX2);
								CLEAR_PIN(ADMUX , ADMUX0);
						}
						break ;

					default:
						switch(U8_positive_differential)
						{
							case 1:
								CLEAR_PIN(ADMUX , ADMUX2);
								SET_PIN(ADMUX , ADMUX0);
								break;
							default:
								CLEAR_PIN(ADMUX , ADMUX2);
								CLEAR_PIN(ADMUX , ADMUX0);
						}
				}
				break;
//case 200x gain
			case 200:
				CLEAR_PIN(ADMUX , ADMUX4);
				SET_PIN(ADMUX , ADMUX3);
				SET_PIN(ADMUX , ADMUX1);
				switch(U8_negative_differential)
				{
					case 2:
						switch(U8_positive_differential)
						{
							case 3:
								SET_PIN(ADMUX , ADMUX2);
								SET_PIN(ADMUX , ADMUX0);
								break;
							default:
								SET_PIN(ADMUX , ADMUX2);
								CLEAR_PIN(ADMUX , ADMUX0);
						}
						break ;
					default:
						switch(U8_positive_differential)
						{
							case 1:
								CLEAR_PIN(ADMUX , ADMUX2);
								SET_PIN(ADMUX , ADMUX0);
								break;
							default:
								CLEAR_PIN(ADMUX , ADMUX2);
								CLEAR_PIN(ADMUX , ADMUX0);
						}
				}
				break;
//default case is 1x gain
			default:
				SET_PIN(ADMUX , ADMUX4);  				/*to select 1x gain you have to set ADMUX4 */
				switch(U8_negative_differential)
				{
					case 2:
						SET_PIN(ADMUX , ADMUX3);		/*to select PIN 2 negative bin SET ADMUX3*/
						switch(U8_positive_differential)
						{
							case 0:
								CLEAR_PIN(ADMUX , ADMUX2);
								CLEAR_PIN(ADMUX , ADMUX1);
								CLEAR_PIN(ADMUX , ADMUX0);
								break;
							case 1:
								CLEAR_PIN(ADMUX , ADMUX2);
								CLEAR_PIN(ADMUX , ADMUX1);
								SET_PIN(ADMUX , ADMUX0);
								break;
							case 3:
								CLEAR_PIN(ADMUX , ADMUX2);
								SET_PIN(ADMUX , ADMUX1);
								SET_PIN(ADMUX , ADMUX0);
								break;
							case 4:
								SET_PIN(ADMUX , ADMUX2);
								CLEAR_PIN(ADMUX , ADMUX1);
								CLEAR_PIN(ADMUX , ADMUX0);
								break;
							case 5:
								SET_PIN(ADMUX , ADMUX2);
								CLEAR_PIN(ADMUX , ADMUX1);
								SET_PIN(ADMUX , ADMUX0);
								break;
							default:
								CLEAR_PIN(ADMUX , ADMUX2);
								SET_PIN(ADMUX , ADMUX1);
								CLEAR_PIN(ADMUX , ADMUX0);
						}
						break ;
					default:
						CLEAR_PIN(ADMUX , ADMUX3);
						switch(U8_positive_differential)
						{
							case 0:
								CLEAR_PIN(ADMUX , ADMUX2);
								CLEAR_PIN(ADMUX , ADMUX1);
								CLEAR_PIN(ADMUX , ADMUX0);
								break;
							case 2:
								CLEAR_PIN(ADMUX , ADMUX2);
								SET_PIN(ADMUX , ADMUX1);
								CLEAR_PIN(ADMUX , ADMUX0);
								break;
							case 3:
								CLEAR_PIN(ADMUX , ADMUX2);
								SET_PIN(ADMUX , ADMUX1);
								SET_PIN(ADMUX , ADMUX0);
								break;
							case 4:
								SET_PIN(ADMUX , ADMUX2);
								CLEAR_PIN(ADMUX , ADMUX1);
								CLEAR_PIN(ADMUX , ADMUX0);
								break;
							case 5:
								SET_PIN(ADMUX , ADMUX2);
								CLEAR_PIN(ADMUX , ADMUX1);
								SET_PIN(ADMUX , ADMUX0);
								break;
							case 6:
								SET_PIN(ADMUX , ADMUX2);
								SET_PIN(ADMUX , ADMUX1);
								CLEAR_PIN(ADMUX , ADMUX0);
								break;
							case 7:
								SET_PIN(ADMUX , ADMUX2);
								SET_PIN(ADMUX , ADMUX1);
								SET_PIN(ADMUX , ADMUX0);
								break;
							default:
								CLEAR_PIN(ADMUX , ADMUX2);
								CLEAR_PIN(ADMUX , ADMUX1);
								SET_PIN(ADMUX , ADMUX0);
						}
			}
	}
}
