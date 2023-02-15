#include "ADC.h"

void init_ADC_LDR(void) //Set up ADC for reading LDR
{
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN;	                //GPIOC clock enable
	LDR_ADC_input_port->MODER|=(3u<<(2*ADC_input_pin));	//ADC input pin is analogue mode
	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;		                //ADC clock enable
	ADC1->SQR1&=~ADC_SQR1_L;						                //set number of conversions per sequence to 1
	ADC1->SQR3&=~ADC_SQR3_SQ1;					                //clear channel select bits
	ADC1->SQR3|= ADC_LDR_Channel;		                    //set channel (LDR)
	ADC1->CR2|=ADC_CR2_ADON;						                //enable ADC
	
}

void init_ADC_POT(void) //Set up ADC for reading POT
{
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;	                //GPIOA clock enable
	POT_ADC_input_port->MODER|=(3u<<(2*ADC_input_pin));	//ADC input pin is analogue mode
	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;		                //ADC clock enable
	ADC1->SQR1&=~ADC_SQR1_L;						                //set number of conversions per sequence to 1
	ADC1->SQR3&=~ADC_SQR3_SQ1;				    	            //clear channel select bits
	ADC1->SQR3|= ADC_POT_Channel;		                    //set channel (POT)
	ADC1->CR2|=ADC_CR2_ADON;					    	            //enable ADC
	 
}

void init_ADC_MIC(void) //Set up ADC for reading MIC
{
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;	                //GPIOA clock enable
	MIC_ADC_input_port->MODER|=(3u<<(2*3));	            //ADC input pin is analogue mode
	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;		                //ADC clock enable
	ADC1->SQR1&=~ADC_SQR1_L;						                //set number of conversions per sequence to 1
	ADC1->SQR3&=~ADC_SQR3_SQ1;					                //clear channel select bits
	ADC1->SQR3|= ADC_MIC_Channel;		                    //set channel  (MIC)
	ADC1->CR2|=ADC_CR2_ADON;					                 	//enable ADC
} 
unsigned short read_adc(void) //Read the data from ADC and return value
{
	ADC1->CR2|=ADC_CR2_SWSTART;				                  //start ADC conversion
	while((ADC1->SR&ADC_SR_EOC)==0){__NOP();} 	        //wait for ADC conversion complete
	return ADC1->DR;									                  //return converted value
}

 double convert_adc_to_voltage(void) //Turn ADC value into Voltage
{
	double a;
	double b;
	double c;
	double d;
	b=read_adc();     //read adc data
	c=3.3;            //top voltage level
	d=4096;           //(2^10)
	a=(b/d)*c;        //recieved value over value levels times by max voltage to get individual voltage
	return a;         //return value as voltage
}	
