#ifndef _DAC_H
#define _DAC_H
#include <stm32f4xx.h>

#define DAC_port	GPIOA
#define DAC_pin		5
#define DAC1_pin 4

void init_DAC(void);               //set up DAC
void init_DAC_1(void);             //set up DAC1

void output_dac(unsigned short d); //output data to DAC2
void output_dac1(unsigned short d); //output data to DAC1
#endif
