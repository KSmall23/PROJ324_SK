#include "timers.h"

void Init_Timer2_dac_square(void)  //sets up tumer for 8kHz square wave
{
	RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;		              //timer 2 clock enabled
	TIM2->DIER|=TIM_DIER_UIE;						              //timer uptdate interrupt enabled
																			              //APB clock is Fcy/2 = 180MHz/2 = 90MHz
	TIM2->PSC=9-1;										                //divide APB clock by 9 = 90MHz/9 = 10MHz
	TIM2->ARR=12;										                  //counter reload value, gives a timer period of around 0.000125ms when F_APB = 90MHz and PSC = 9
	TIM2->CNT=0;												              //zero timer counter
	NVIC->ISER[TIM2_IRQn>>5]|=1<<(TIM2_IRQn&0x1F);		//timer 2 global interrupt enabled
	TIM2->CR1|=TIM_CR1_CEN;						               	//start timer counter
}
void Init_Timer2_dac_tri(void)    //sets up timer for 4kHz triangle wave
{
	RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;		              //timer 2 clock enabled
	TIM2->DIER|=TIM_DIER_UIE;						              //timer uptdate interrupt enabled
																			              //APB clock is Fcy/2 = 180MHz/2 = 90MHz
	TIM2->PSC=9-1;										                //divide APB clock by 9 = 90MHz/9 = 10MHz
	TIM2->ARR=25;										                  //counter reload value, gives a timer period of 0.00025ms when F_APB = 90MHz and PSC = 9
	TIM2->CNT=0;												              //zero timer counter
	NVIC->ISER[TIM2_IRQn>>5]|=1<<(TIM2_IRQn&0x1F);    //timer 2 global interrupt enabled
	TIM2->CR1|=TIM_CR1_CEN;						                //start timer counter
}
void Init_Timer2_dac_sin(void)   //sets up timer for 2kHz sine wave
{  
	RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;		              //timer 2 clock enabled
	TIM2->DIER|=TIM_DIER_UIE;						              //timer uptdate interrupt enabled
																			              //APB clock is Fcy/2 = 180MHz/2 = 90MHz
	TIM2->PSC=11-1;										                //divide APB clock by 11 = 90MHz/11 = 8.18MHz
	TIM2->ARR=2;										                  //counter reload value, gives a timer period of around 0.0000247ms when F_APB = 90MHz and PSC = 11
	TIM2->CNT=0;												              //zero timer counter
	NVIC->ISER[TIM2_IRQn>>5]|=1<<(TIM2_IRQn&0x1F);		//timer 2 global interrupt enabled
	TIM2->CR1|=TIM_CR1_CEN;						               	//start timer counter
}

void Init_Timer4_1sec(void)    //sets up timer for 1 second interrupt
{
	RCC->APB1ENR|=RCC_APB1ENR_TIM4EN;		              //timer 4 clock enabled
	TIM4->DIER|=TIM_DIER_UIE;						              //timer uptdate interrupt enabled
																			              //APB clock is Fcy/2 = 180MHz/2 = 90MHz
	TIM4->PSC=25600-1;									              //25600 = 90MHz/25600Hz = 351562.5Hz
	TIM4->ARR=3515;										                //counter reload value, gives a timer period of 1s when F_APB = 90MHz and PSC = 25600
	TIM4->CNT=0;												              //zero timer counter
	NVIC->ISER[TIM4_IRQn>>5]|=1<<(TIM4_IRQn&0x1F);		//timer 4 global interrupt enabled
	TIM4->CR1|=TIM_CR1_CEN;							              //start timer counter
}

void Init_Timer7_10sec(void)   //sets up timer for 10 second interrupt
{
	RCC->APB1ENR|=RCC_APB1ENR_TIM7EN;		              //timer 7 clock enabled
	TIM7->DIER|=TIM_DIER_UIE;						              //timer uptdate interrupt enabled
																			              //APB clock is Fcy/2 = 180MHz/2 = 90MHz
	TIM7->PSC=25600-1;									              //25600 = 90MHz/25600Hz = 351562.5Hz
	TIM7->ARR=35150;										              //counter reload value, gives a timer period of 10s when F_APB = 90MHz and PSC = 25600
	TIM7->CNT=0;												              //zero timer counter
	NVIC->ISER[TIM7_IRQn>>5]|=1<<(TIM7_IRQn&0x1F);		//timer 7 global interrupt enabled
	TIM7->CR1|=TIM_CR1_CEN;							              //start timer counter
}

void Init_Timer3_BlinkyRed (void)  //sets up timer  for 4.8Hz blink of red on Nucleo board
{
  RCC->APB1ENR|=RCC_APB1ENR_TIM3EN;		//timer 3 clock enabled
	TIM3->DIER|=TIM_DIER_UIE;						//timer uptdate interrupt enabled
																			//APB clock is Fcy/2 = 180MHz/2 = 90MHz
	TIM3->PSC=500-1;										//divide APB clock by 500 = 90MHz/500Hz = 180kHz
	TIM3->ARR=37500;									  //counter reload value, gives a timer frequency of 4.8Hz when F_APB = 90MHz and PSC = 25600
	TIM3->CNT=0;												//zero timer counter
	NVIC->ISER[0]|=(1<<29);						  //timer 3 global interrupt enabled
	TIM3->CR1|=TIM_CR1_CEN;							//start timer counter
}




//TIMERS TO CHANGE TONE OF BUZZER

void Init_Timer5_buzzer_A(void) //sets timer for Buzzer tone a
{
	RCC->APB1ENR|=RCC_APB1ENR_TIM5EN;		              //timer 5 clock enabled
	TIM5->DIER|=TIM_DIER_UIE;						              //timer uptdate interrupt enabled
                                                   	//APB clock is Fcy/2 = 180MHz/2 = 90MHz
	TIM5->PSC=45-1;										                //divide APB clock by 45 = 90MHz/45 = 2MHz
	TIM5->ARR=4545;										                 //counter reload value, gives a timer period of around 440Hz when F_APB = 90MHz and PSC = 45
	TIM5->CNT=0;												              //zero timer counter
	NVIC->ISER[TIM5_IRQn>>5]|=1<<(TIM5_IRQn&0x1F);		//timer 5 global interrupt enabled
	TIM5->CR1|=TIM_CR1_CEN;						               	//start timer counter
}

void Init_Timer5_buzzer_B(void) //sets timer for Buzzer tone b
{
	RCC->APB1ENR|=RCC_APB1ENR_TIM5EN;		              //timer 5 clock enabled
	TIM5->DIER|=TIM_DIER_UIE;						              //timer uptdate interrupt enabled
                                                   	//APB clock is Fcy/2 = 180MHz/2 = 90MHz
	TIM5->PSC=45-1;										                //divide APB clock by 2 = 90MHz/45 = 2MHz
	TIM5->ARR=4057;										                  //counter reload value, gives a timer period of around 493 when F_APB = 90MHz and PSC = 45
	TIM5->CNT=0;												              //zero timer counter
	NVIC->ISER[TIM5_IRQn>>5]|=1<<(TIM5_IRQn&0x1F);		//timer 5 global interrupt enabled
	TIM5->CR1|=TIM_CR1_CEN;						               	//start timer counter
}
void Init_Timer5_buzzer_C(void) //sets timer for Buzzer tone c
{
	RCC->APB1ENR|=RCC_APB1ENR_TIM5EN;		              //timer 5 clock enabled
	TIM5->DIER|=TIM_DIER_UIE;						              //timer uptdate interrupt enabled
                                                   	//APB clock is Fcy/2 = 180MHz/2 = 90MHz
	TIM5->PSC=20-1;										                //divide APB clock by 20 = 90MHz/20 = 4.8MHz
	TIM5->ARR=8600;										                 //counter reload value, gives a timer frequency of around 523.25Hz when F_APB = 90MHz and PSC = 20
	TIM5->CNT=0;												              //zero timer counter
	NVIC->ISER[TIM5_IRQn>>5]|=1<<(TIM5_IRQn&0x1F);		//timer 5 global interrupt enabled
	TIM5->CR1|=TIM_CR1_CEN;						               	//start timer counter
}
void Init_Timer5_buzzer_D(void) //sets timer for Buzzer tone d
{
	RCC->APB1ENR|=RCC_APB1ENR_TIM5EN;		              //timer 5 clock enabled
	TIM5->DIER|=TIM_DIER_UIE;						              //timer uptdate interrupt enabled
                                                   	//APB clock is Fcy/2 = 180MHz/2 = 90MHz
	TIM5->PSC=50-1;										                //divide APB clock by 50 = 90MHz/50 = 1.8MHz
	TIM5->ARR=3066;										                //counter reload value, gives a timer frequency of around 587.33Hz when F_APB = 90MHz and PSC = 50
	TIM5->CNT=0;												              //zero timer counter
	NVIC->ISER[TIM5_IRQn>>5]|=1<<(TIM5_IRQn&0x1F);		//timer 5 global interrupt enabled
	TIM5->CR1|=TIM_CR1_CEN;						               	//start timer counter
}
void Init_Timer5_buzzer_E(void) //sets timer for Buzzer tone e
{
	RCC->APB1ENR|=RCC_APB1ENR_TIM5EN;		              //timer 5 clock enabled
	TIM5->DIER|=TIM_DIER_UIE;						              //timer uptdate interrupt enabled
                                                   	//APB clock is Fcy/2 = 180MHz/2 = 90MHz
	TIM5->PSC=50-1;										                //divide APB clock by 50 = 90MHz/50 = 1.8MHz
	TIM5->ARR=2731;										                //counter reload value, gives a timer frequency of around 629.25Hz when F_APB = 90MHz and PSC = 50
	TIM5->CNT=0;												              //zero timer counter
	NVIC->ISER[TIM5_IRQn>>5]|=1<<(TIM5_IRQn&0x1F);		//timer 5 global interrupt enabled
	TIM5->CR1|=TIM_CR1_CEN;						               	//start timer counter
}
void Init_Timer5_buzzer_F(void) //sets timer for Buzzer tone f
{
	RCC->APB1ENR|=RCC_APB1ENR_TIM5EN;		              //timer 5 clock enabled
	TIM5->DIER|=TIM_DIER_UIE;						              //timer uptdate interrupt enabled
                                                   	//APB clock is Fcy/2 = 180MHz/2 = 90MHz
	TIM5->PSC=50-1;										                //divide APB clock by 50 = 90MHz/50 = 1.8MHz
	TIM5->ARR=2578;										                 //counter reload value, gives a timer frequency of around 698.46Hz when F_APB = 90MHz and PSC = 50
	TIM5->CNT=0;												              //zero timer counter
	NVIC->ISER[TIM5_IRQn>>5]|=1<<(TIM5_IRQn&0x1F);		//timer 5 global interrupt enabled
	TIM5->CR1|=TIM_CR1_CEN;						               	//start timer counter
}
void Init_Timer5_buzzer_G(void) //sets timer for Buzzer tone g
{
	RCC->APB1ENR|=RCC_APB1ENR_TIM5EN;		              //timer 5 clock enabled
	TIM5->DIER|=TIM_DIER_UIE;						              //timer uptdate interrupt enabled
                                                   	//APB clock is Fcy/2 = 180MHz/2 = 90MHz
	TIM5->PSC=50-1;										                //divide APB clock by 50 = 90MHz/50 = 1.8MHz
	TIM5->ARR=2296;										                //counter reload value, gives a timer frequency of around 783.99Hz when F_APB = 90MHz and PSC = 50
	TIM5->CNT=0;												              //zero timer counter
	NVIC->ISER[TIM5_IRQn>>5]|=1<<(TIM5_IRQn&0x1F);		//timer 5 global interrupt enabled
	TIM5->CR1|=TIM_CR1_CEN;						               	//start timer counter
}

void Init_Timer5_buzzer_off_low(void)    //Buzzer speed at 50kHz, outside of Human Hearing range so effectively off.
{
	RCC->APB1ENR|=RCC_APB1ENR_TIM5EN;		              //timer 5 clock enabled
	TIM5->DIER|=TIM_DIER_UIE;						              //timer uptdate interrupt enabled
                                                   	//APB clock is Fcy/2 = 180MHz/2 = 90MHz
	TIM5->PSC=9-1;										                //divide APB clock by 9 = 90MHz/9 = 10MHz
	TIM5->ARR=200;										                //counter reload value, gives a timer frequency of around 50kHz when F_APB = 90MHz and PSC = 9
	TIM5->CNT=0;												              //zero timer counter
	NVIC->ISER[TIM5_IRQn>>5]|=1<<(TIM5_IRQn&0x1F);		//timer 5 global interrupt enabled
	TIM5->CR1|=TIM_CR1_CEN;						               	//start timer counter
}
void Init_Timer5_buzzer_off_high(void)   //Buzzer speed at 100kHz, outside of Human Hearing range so effectively off.
{
	RCC->APB1ENR|=RCC_APB1ENR_TIM5EN;		              //timer 5 clock enabled
	TIM5->DIER|=TIM_DIER_UIE;						              //timer uptdate interrupt enabled
                                                   	//APB clock is Fcy/2 = 180MHz/2 = 90MHz
	TIM5->PSC=9-1;										                //divide APB clock by 9 = 90MHz/9 = 10MHz
	TIM5->ARR=100;										                //counter reload value, gives a timer frequency of around 100kHz when F_APB = 90MHz and PSC = 9
	TIM5->CNT=0;												              //zero timer counter
	NVIC->ISER[TIM5_IRQn>>5]|=1<<(TIM5_IRQn&0x1F);		//timer 5 global interrupt enabled
	TIM5->CR1|=TIM_CR1_CEN;						               	//start timer counter
}