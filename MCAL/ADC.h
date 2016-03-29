/*
 * ADC.h
 *
 *  Created on: Mar 26, 2016
 *      Author: Alttawab
 */

#ifndef MCAL_ADC_H_
#define MCAL_ADC_H_
void void_adc_init_single_ended(U8_t U8_port ,U8_t U8_pin );
U16_t U16_adc_read();
void void_adc_enable(U8_t U8_state);
void void_adc_prescaler_selup() ;
void adc_select_refrence(U8_t U8_Aref_or_aVcc_or_Internal_2v56_ref);
void void_adc_init_differential_input (U8_t U8_port , U8_t U8_positive_differential, U8_t U8_negative_differential , U8_t U8_gain);


#endif /* MCAL_ADC_H_ */
