/*
 * ADC.c
 *
 *  Created on: Mar 26, 2016
 *      Author: Alttawab
 */
#include "D_IO.h"
#include "adc.h"

/*ADC SETUP*/
//#define FREQUANCY_PRE_SCALER 64  /*Uncomment if user need specific prescaler */
#define ADC_REFERNCE_VOLTAGE 'A'
#define SINGLE_ENDED_MODE

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


void void_adc_init(U8_t U8_port ,U8_t U8_pin )
{
	S8_DIO_init_pin(U8_port ,U8_pin,INPUT); 		/*make pin input */
	void_adc_enable(SET);							/*Enable the ADC*/
	void void_adc_prescaler_setup();				/*select the prescaler*/
	adc_select_refrence(ADC_REFERNCE_VOLTAGE);						/*select reference to be Avref */

#ifdef SINGLE_ENDED_MODE
	CLEAR_PIN(ADMUX , ADMUX0);						/*						  A0*/
	CLEAR_PIN(ADMUX , ADMUX2);						/*			analoge			*/
	CLEAR_PIN(ADMUX , ADMUX1);						/*					channel	*/
	if(U8_pin<8)
	ADMUX|=U8_pin;
	CLEAR_PIN(ADMUX , ADMUX3);						/*		the					*/
	CLEAR_PIN(ADMUX , ADMUX4);						/*Select					*/
#endif
}


/*read pin*/
U16_t U16_adc_read()
{
	U8_t U8_analoge_data_low ;
	U8_t U8_analoge_data_high;
	U16_t U16_value ;
	U8_analoge_data_low =0 ;
	U8_analoge_data_high=0;
	U16_value =0;
	SET_PIN(ADCSRA , ADSC);
	while(!(1<<ADIF)&(ADCSRA));
	ADCSRA |= (1<<ADIF) ;
	U8_analoge_data_low = ADCL ;
	U8_analoge_data_high = ADCH ;
	U16_value = (((U16_t )U8_analoge_data_high)<<8) +U8_analoge_data_low ;
	return (U16_value) ;
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


/*todo make differntial input mode */
