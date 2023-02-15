#include "DAC.h"


void init_DAC(void) //set up DAC2
{
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;			//DAC port clock enable
	DAC_port->MODER|=(3u<<(2*DAC_pin));			//DAC output pin set as anaglogue
	RCC->APB1ENR|=RCC_APB1ENR_DACEN;				//DAC clock enable
	DAC->CR|=DAC_CR_EN2;										//DAC 2 enabled
}

void init_DAC_1(void) //set up DAC1
{
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;			//DAC port clock enable
	DAC_port->MODER|=(3u<<(2*DAC1_pin));		//DAC output pin set as anaglogue
	RCC->APB1ENR|=RCC_APB1ENR_DACEN;				//DAC clock enable
	DAC->CR|=DAC_CR_EN1;										//DAC 1 enabled
}
void output_dac(unsigned short d) //output data to DAC2
{
	DAC->DHR12R2=d;			//write data byte to DAC 2 output register
}

void output_dac1(unsigned short d) //output data to DAC1
{
	DAC->DHR12R1=d;			//write data byte to DAC 1 output register
}