#ifndef _EXT_INTERRUPTS_H_
#define _EXT_INTERRUPTS_H_
#include <stm32f4xx.h>

void InitBlueButton_EXTI (void); //blue button on port C pin 13, external interrupt set up for button press
void EXTI15_10_IRQHandler (void); //Interrupt service routine for Blue Button, hold mode and pedestrian button

#endif