#ifndef HAL_LED_H_
#define HAL_LED_H_

#include "..\ServiceLayer\stdTypes.h"
#define LED_PORT 'D'
#define LED1 4
#define LED2 5#define LED3 6#define LED4 7void void_led_init_all_led();
void void_led_init_led_1();
void void_led_init_led_2();
void void_led_init_led_3();
void void_led_init_led_4();
void void_led_all_led_on();
void void_led_1_on();
void void_led_2_on();
void void_led_3_on();
void void_led_4_on();
void void_led_all_led_off();
void void_led_1_off();
void void_led_2_off();
void void_led_3_off();
void void_led_4_off();
void void_led_on(U8_t LedNumber) ;
void void_led_off(U8_t LedNumber);

#endif // LED_H
