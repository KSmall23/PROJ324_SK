#ifndef _BUZZER_H_
#define _BUZZER_H_
#include <stm32f429xx.h>

#define BuzzerPort GPIOB
#define Buzzer 13

void config_buzzer (void);  //config buzzer
void buzzer_on (void);      //turns buzzer on
void buzzer_off (void);     //turns buzzer off
void toggle_buzzer (void);  //flips buzzer to opposite of last state (on or off) it

void Tune_1 (void);         //plays tune 1, plays though different notes as counter goes up, calling on the timers at different speeds
void Tune_2 (void);         //plays tune 2, plays though different notes as counter goes up, calling on the timers at different speeds

#endif