/*
 * KeyPad.h
 *
 *  Created on: Mar 13, 2016
 *      Author: Alttawab
 */

#ifndef HAL_KEYPAD_H_
#define HAL_KEYPAD_H_
#include "..\ServiceLayer\stdTypes.h"
void void_keyPad_init();
void void_keyPad_wait_keyRelease();
void void_keyPad_wait_keyPress();
U8_t U8_keyPad_scanKey();
#endif /* HAL_KEYPAD_H_ */
