/*
 * SevenSegments.h
 *
 *  Created on: Mar 17, 2016
 *      Author: Alttawab
 */


#ifndef HAL_SEVENSEGMENTS_H_
#define HAL_SEVENSEGMENTS_H_
#include "../ServiceLayer/stdTypes.h"

#define SEVSEG_DATA_PORT 'B'
#define SEVSEG_ENABLE_PORT 'C'
#define SEVSEG_FLOAT_PORT 'D'
#define SEVSEG_DATA0 0
#define SEVSEG_DATA1 1
#define SEVSEG_DATA2 2
#define SEVSEG_DATA3 3
#define SEVSEG_EN1 4
#define SEVSEG_EN2 5
#define SEVSEG_EN3 3
#define SEVSEG_EN4 2
#define SEVSEG_FLOAT_ENABLE 5
#define DELAYS 2
#define MAXIMUM_VALUE 9999
#define MINIMUM_VLAUE 0

void void_sevSeg_init();
void void_sevSeg_dispaly(U16_t U16_numeric_value);
U16_t U16_sevSeg_dispaly_digit(U16_t U16_numeric_value,  U8_t U8_digit ) ;

#endif /* HAL_SEVENSEGMENTS_H_ */
