#ifndef _ADC_H
#define _ADC_H
#include <stm32f4xx.h>

#define LDR_ADC_input_port		GPIOC
#define POT_ADC_input_port		GPIOA
#define MIC_ADC_input_port		GPIOA
#define ADC_input_pin			0
#define ADC_LDR_Channel		10
#define ADC_POT_Channel		0
#define ADC_MIC_Channel		3

void init_ADC_LDR(void);             //Set up ADC for reading LDR
void init_ADC_POT(void);             //Set up ADC for reading POT
void init_ADC_MIC(void);             //Set up ADC for reading MIC
unsigned short read_adc(void);       //Read the data from ADC and return value
double convert_adc_to_voltage(void); //Turn ADC value into Voltage
#endif 
