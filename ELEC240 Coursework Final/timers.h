#ifndef _TIMERS_H_
#define _TIMERS_H_
#include <stm32f429xx.h>


#define TIM2_IRQn 28
#define TIM5_IRQn 50
#define TIM4_IRQn 30
#define TIM7_IRQn 55
#define TIM12_IRQn 43



void Init_Timer2_dac_sin(void);     //sets up timer to to create 2kHz sine
void Init_Timer2_dac_tri(void);     //sets up timer to to create 4kHz triangle
void Init_Timer2_dac_square(void);  //sets up timer to to create 8kHz square
void Init_Timer4_1sec(void);        //sets up timer for 1 second interrupt
void Init_Timer7_10sec(void);       //sets up timer for 10 second interrupt
void Init_Timer3_BlinkyRed (void);  //sets up timer  for 4.8Hz blink of red on Nucleo board

void Init_Timer5_buzzer_A(void);    //sets timer for Buzzer tone a
void Init_Timer5_buzzer_B(void);    //sets timer for Buzzer tone b
void Init_Timer5_buzzer_C(void);    //sets timer for Buzzer tone c 
void Init_Timer5_buzzer_D(void);    //sets timer for Buzzer tone d
void Init_Timer5_buzzer_E(void);    //sets timer for Buzzer tone e
void Init_Timer5_buzzer_F(void);    //sets timer for Buzzer tone f
void Init_Timer5_buzzer_G(void);    //sets timer for Buzzer tone g

void Init_Timer5_buzzer_off_low(void);   //Buzzer speed at 50kHz, outside of Human Hearing range so effectively off.
void Init_Timer5_buzzer_off_high(void);  //Buzzer speed at 100kHz, outside of Human Hearing range so effectively off.


#endif