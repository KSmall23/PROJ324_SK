#include "Delay.h"	

void Init_Timer3(void) //sets up timer 3 without interrupt
{
  RCC->APB1ENR|=RCC_APB1ENR_TIM3EN;		 //timer 3 clock enabled
   																		 //APB clock is Fcy/2 = 180MHz/2 = 90MHz
	TIM3->PSC=90-1;										   //divide APB clock by 90 = 90MHz/90Hz = 1MHz
	TIM3->ARR=0xffff;										 //counter reload value, counts to top when F_APB = 90MHz and PSC = 90
	TIM3->CNT=0;												 //zero timer counter			 
	TIM3->CR1|=TIM_CR1_CEN;              //start timer counter
}	
void WaiT3 (unsigned int Delay_us) //uS delay defined by user
{
	unsigned int start;
	unsigned int B;
 RCC->APB1ENR|=RCC_APB1ENR_TIM3EN;      //enable timer 3 clock		
 TIM3->CR1|=TIM_CR1_CEN;                //start timer 3 clock
 start = TIM3->CNT;                     //start is start value for clock
 B=0; 
 	
do
{
	unsigned int count=TIM3->CNT;        //variable count current value for count
  B = count-start;                     //B is current value minus initial value
} while(B<Delay_us);                   //stay in loop until B is as large as desired delay

}

		
void delay_100ms_blocking(void)       //100ms BLOCKING DELAY    
{
	unsigned int i;				                              //increment a variable to waste time
	for(i=0; i<SystemCoreClock/180; i++) {__NOP();};		//incrementing a variable from 0 to 4,500,000 takes 100ms when MCU speed is 180MHz
}


 
void blocking_delay_ms(float a) //user defined ms BLOCKING DELAY
{
	float b=0;  //creat count variable
  a=a/100;    //divide a by 100 because each count is 100ms
	while (b<=a)//wait until count variable same as a
	{
    delay_100ms_blocking(); //wait 100ms
    b++;	//increment count	
	};	
}
