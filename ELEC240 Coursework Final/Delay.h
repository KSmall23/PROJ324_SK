#ifndef __DELAY_H
#define __DELAY_H
#include "stm32f4xx.h"


void Init_Timer3(void);             //sets up timer 3 without interrupt
void WaiT3 (unsigned int Delay_us); //uS delay defined by user
void delay_100ms_blocking(void);    //100ms BLOCKING DELAY  
void blocking_delay_ms(float a);    //user defined ms BLOCKING DELAY


#endif
