/*
 * ADC.h
 *
 *  Created on: Mar 26, 2016
 *      Author: Alttawab
 */

#ifndef MCAL_ADC_H_
#define MCAL_ADC_H_
void void_adc_init_single_ended_input(U8_t U8_port ,U8_t U8_pin );
void void_adc_init_differential_input (U8_t U8_port , U8_t U8_positive_differential, U8_t U8_negative_differential , U8_t U8_gain);
S16_t S16_adc_read_differential_input();
U16_t U16_adc_read_single_ended_input();
void void_adc_enable(U8_t U8_state);
void void_adc_prescaler_selup() ;
void adc_select_refrence(U8_t U8_Aref_or_aVcc_or_Internal_2v56_ref);


#endif /* MCAL_ADC_H_ */
