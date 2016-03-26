/*
 * KeyPad.h
 *
 *  Created on: Mar 13, 2016
 *      Author: Alttawab
 */

#ifndef HAL_KEYPAD_H_
#define HAL_KEYPAD_H_

#include "..\ServiceLayer\stdTypes.h"
#include "..\MCAL\D_IO.h"
#include <util/delay.h>

#define KEYPAD_PORT 'A'
#define ROW1 4			//OUTPUT
#define ROW2 3			//OUTPUT
#define ROW3 2			//OUTPUT
#define COLUMN1 7		//INPUT
#define COLUMN2 6		//INTPUT
#define COLUMN3 5		//INTPUT

void void_keyPad_init();
void void_keyPad_wait_keyRelease();
void void_keyPad_wait_keyPress();
bool bool_keyPad_wait_keyPress();
bool bool_keyPad_wait_keyPress_open(U8_t U8_max) ;

U8_t U8_keyPad_scanKey();
#endif /* HAL_KEYPAD_H_ */
