#include <stm32f4xx.h>
#include "PLL_Config.c"
#include "ADC.c"            //holds functions relating to ADC
#include "DAC.c"            //holds functions relating to DAC
//#include "LED.c"            //holds functions relating to all LEDs
//#include "usart.c"          //holds functions relating to the USART
//#include "lcd.c"            //holds functions relating to LCD
//#include "buttons.c"        //holds functions relating to Blue button and switches
//#include "latches.c"        //holds functions relating to use of LED bars and 7segment display
#include "timers.c"         //holds timer functions 
#include "arrays.h"         //holds arrays
//#include "buzzer.c"         //holds functions using buzzer
//#include "ext_interrupts.h" //holds function for blue button interrupt and HOLD mode; link to .c file found in 'traffic_lights.c'
//#include "traffic_lights.c" //holds functions for the traffic light system


//unsigned short POT_D; //global variable to store reading on POT
//unsigned short LDR_D; //global variable to store reading on LDR
//unsigned short MIC_D; //global variable to store reading on MIC

//double POT_V; //global variable to store voltage of POT
//double LDR_V; //global variable to store voltage of LDR
//double MIC_V; //global variable to store voltage of MIC

//static int LCD_display=1;  //global variable to control which voltage is displayed on LCD (POT, MIC, LDR)

int main(void)
{
	PLL_Config();              //set set clock speed to 180Mhz
	SystemCoreClockUpdate();   //set clock speed to 180Mhz
//	initLCD();        //config LCD
//	init_USART();     //config USART to 230400 baud rate
	init_DAC();		    //config DAC2
	init_DAC_1();     //config DAC1
//	config_buttons(); //config buttons and switches
//	config_Lights();  //config all LEDs and lights
//	//config_buzzer();  //comnfig buzzer
//	Init_Timer3();    //config timer 3
//	Init_Timer3_BlinkyRed(); //config timer 3 for 4.8Hz flashes
//	Init_Timer4_1sec(); //config timer 4 to interrupt every 1 second
//	Init_Timer7_10sec(); //config timer 7 to interrupt every 10 seconds
//	InitBlueButton_EXTI(); //config external interrupt to serve blue button
//	Init_Timer5_buzzer_off_low(); //config timer 5 for turning the buzzer off
	
	Init_Timer2_dac_sin();
	while(1)
	{}
}

	

void TIM2_IRQHandler(void)			//TIMER 2 INTERRUPT SERVICE ROUTINE for outputing to DACs, varied speeds depending on which wave its outputing 
{
TIM2->SR&=~TIM_SR_UIF;				//clear interrupt flag in status register 	
static int count=0;           //create static variable 'count' to go through arrays
	                      //output=3 when C has been typed or pressed, gives sine wave on DAC2
  output_dac(carry[count]);   //output=3 when C has been typed or pressed, gives sine wave on DAC2 

	count=count+99;  //goes through arrays at incrementy of ten steps
  
	if(count>6799) //reset count value to 0 once array gone through completely
   {            //reset count value to 0 once array gone through completely
   count=0;     //reset count value to 0 once array gone through completely
   }		        //reset count value to 0 once array gone through completely
}



                     


