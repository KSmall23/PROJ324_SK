#include "ext_interrupts.h"
#include "usart.h"
#include "lcd.h"
#include "buttons.h"
#include "Delay.h"
#include "Led.h"
#include "usart.h"
#include "timers.h"
#include "buzzer.h"

static int white_man=0; //global variable to control pedestrian button

void InitBlueButton_EXTI (void)       //blue button on port C pin 13, external interrupt set up for button press
{
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;                    //enable clock for port blue button is on
RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;                   //enable clock for external interrupt
GPIOC->MODER &= ~GPIO_MODER_MODER13;                    //configure blue button on pin 13
GPIOC->PUPDR &= ~GPIO_MODER_MODER13;
SYSCFG->EXTICR[3] &= ~(SYSCFG_EXTICR4_EXTI13_Msk);      //configure the extenal interrupt for port C pin 13 which is held in the fourth part of the register 
SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
EXTI->IMR |= EXTI_IMR_IM13;                             //mask external interrupt to pin 13 only
EXTI->RTSR |= EXTI_RTSR_TR13;                           //set interrupt to occur on rising edge
//EXTI->FTSR |= EXTI_FTSR_TR13;                           //set interrupt to occur on falling edge
NVIC_EnableIRQ(EXTI15_10_IRQn);                         //enable global interrupt for EXT15_10
NVIC_SetPriority(EXTI15_10_IRQn, 0);                    //give this external interrupt top priority (will interrupt everything)
}




void EXTI15_10_IRQHandler (void) //Interrupt service routine for Blue Button, hold mode and pedestrian button
{

  if (EXTI->PR & EXTI_PR_PR13)    //check that it was the blue button that was pressed (this is done because this external interrupt is for all peripherals on pins 10-15
   {
	  send_usart_string("blue button pressed\n\r"); //print to USART to show button pressed
    int bb;		                    //create blue button reader
    blocking_delay_ms(1000);      //wait for long press
		bb=read_Blue_Button();        //read blue button
		
		 if(bb==0)                    //if not long press set up for white man set up
     {
		  white_man=1;
		  do                       //wait for blue button to be released           
      {                        //wait for blue button to be released
	     bb=read_Blue_Button();  //wait for blue button to be released  
	    }while(bb!=0);           //wait for blue button to be released			
			 
		 }		
		 //HOLD MODE
		 if(bb!=0)                 //if long press and still being pressed after wait go into hold mode
     {
      
			do                       //wait for blue button to be released           
      {                        //wait for blue button to be released
	     bb=read_Blue_Button();  //wait for blue button to be released  
	    }while(bb!=0);           //wait for blue button to be released			
			
			clear_LCD(); 
      select_LINE(2);
			printf("HOLD");             //print HOLD on bottom of LCD and send to USART
			GPIOB_led_off(Blinky_Red);  //turn of Red LED on Nucleo
		  GPIOB_led_on(Blinky_Green);
			int test;                   //test condition to be met to get out of Hold mode
      test=0;		                  //test condition is zero until blue button has had a long press 	  		
		  do
      {
			 bb=0;
			 do
			 {
			  bb=read_Blue_Button();
			 }while(bb==0);           //wait for blue button to be pressed
			 blocking_delay_ms(1000); //wait for long press
       bb=read_Blue_Button();   //read blue button 
			 if(bb!=0)                //if the blue button is still being pressed then test condition has been met and can leave loop and thus the interrupt
			 {
			  test=1;
			 }
		  }while(test==0);         //wait for blue button to be held for 'long press'
  	  do                       //wait for blue button to be released	
      {                        //wait for blue button to be released	 
	     bb=read_Blue_Button();  //wait for blue button to be released	
	    }while(bb!=0);           //wait for blue button to be released	
		 }		  	
     EXTI->PR |= EXTI_PR_PR13;       //clear interrupt flag 
    }
}