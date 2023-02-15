#include "buzzer.h"
#include "timers.h"

void config_buzzer (void)  //config buzzer
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;      //turns GPIOB clock on
	BuzzerPort->MODER |= (1<<Buzzer*2);       //sets buzzer pin to output (10)
  BuzzerPort->MODER &= ~(1<<(1+Buzzer*2));  //sets buzzer pin to output (10)
	
	BuzzerPort->PUPDR &= ~(1<<Buzzer*2);      //sets buzzer pin to pull up (01)
	BuzzerPort->PUPDR |= (1<<(1+Buzzer*2));   //sets buzzer pin to pull up (01)
	
	BuzzerPort->OTYPER &= ~(1<<Buzzer*2);     //sets buzzer pin topush-pull (0)

}

void buzzer_on (void) //turns buzzer on
{
 BuzzerPort->BSRR=(1<<Buzzer);
}	
void buzzer_off (void) //turns buzzer off
{
 BuzzerPort->BSRR=(1<<(16+Buzzer));
}	
void toggle_buzzer (void) //flips buzzer to opposite of last state (on or off) it
{
 BuzzerPort->ODR ^= (1<<Buzzer); 
}	


static int tune_counter=1; //global vairable used to count through tune

void Tune_1 (void)  //plays tune 1, plays though different notes as counter goes up, calling on the timers at different speeds
{	
		if (tune_counter==1)
		{
		Init_Timer5_buzzer_A();
		}	
		if (tune_counter==2)
		{
	  Init_Timer5_buzzer_G();
		}	
		if (tune_counter==3)
		{
		Init_Timer5_buzzer_A();
		}	
		if (tune_counter==4)
		{
		Init_Timer5_buzzer_C();
		}	
		if (tune_counter==5)
		{
		Init_Timer5_buzzer_F();
		}	
		if (tune_counter==6)
		{
		Init_Timer5_buzzer_C();
		}	
		if (tune_counter==7)
		{
		Init_Timer5_buzzer_A();
		}	
		if (tune_counter==8)
		{
		Init_Timer5_buzzer_B();
		}	
		if (tune_counter==9)
		{
	  Init_Timer5_buzzer_A();
		}
		if (tune_counter==10)
		{
	  Init_Timer5_buzzer_off_high(); //turns buzzer off at end of tune
		}



	}		

void Tune_2 (void) //plays tune 2, plays though different notes as counter goes up, calling on the timers at different speeds
{
		if (tune_counter==1)
		{
		Init_Timer5_buzzer_G();
		}	
		if (tune_counter==2)
		{
	  Init_Timer5_buzzer_G();
		}	
		if (tune_counter==3)
		{
		Init_Timer5_buzzer_A();
		}	
		if (tune_counter==4)
		{
		Init_Timer5_buzzer_A();
		}	
		if (tune_counter==5)
		{
		Init_Timer5_buzzer_off_high();
		}	
		if (tune_counter==6)
		{
		Init_Timer5_buzzer_D();
		}	
		if (tune_counter==7)
		{
		Init_Timer5_buzzer_E();
		}	
		if (tune_counter==8)
		{
		Init_Timer5_buzzer_F();
		}	
		if (tune_counter==9)
		{
	  Init_Timer5_buzzer_G();
		}
		if (tune_counter==10)
		{
	  Init_Timer5_buzzer_off_high(); //turns buzzer of at end of tune
		}



}