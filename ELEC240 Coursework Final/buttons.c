#include "buttons.h"
#include "Led.h"
#include "timers.h"
#include "usart.h"
#include "lcd.h"

void config_Blue_Button(void)  //config Blue Button on PC 13
{
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;              //enable GPIOC
BB_input_port->MODER &= ~(1<<(BlueButton*2));     //Set Blue Button to input (00)
BB_input_port->MODER &= ~(1<<(1+(BlueButton*2))); //Set Blue Button to input (00)	 
}

void config_SWA(void)  //config Switch A on PG 0
{
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;       //enable GPIOG
SW_input_port->MODER &= ~(1<<(SWA*2));     //Set switch A to input (00)
SW_input_port->MODER &= ~(1<<(1+(SWA*2))); //Set switch A to input (00)
SW_input_port->PUPDR |= (1<<(1+SWA*2));    //set pin for SWA to pull down
SW_input_port->PUPDR &= ~(1<<(SWA*2));		 //set pin for SWA to pull down
}

void config_SWB(void)  //config Switch B on PG 1
{
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;       //enable GPIOG
SW_input_port->MODER &= ~(1<<(SWB*2));     //Set switch B to input (00)
SW_input_port->MODER &= ~(1<<(1+(SWB*2))); //Set switch B to input (00)
SW_input_port->PUPDR |= (1<<(1+SWB*2));    //set pin for SWB to pull down
SW_input_port->PUPDR &= ~(1<<(SWB*2));	   //set pin for SWB to pull down
}
void config_SWC(void)  //config Switch C on PG 2
{
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;       //enable GPIOG
SW_input_port->MODER &= ~(1<<(SWC*2));     //Set switch C to input (00)
SW_input_port->MODER &= ~(1<<(1+(SWC*2))); //Set switch C to input (00) 
SW_input_port->PUPDR |= (1<<(1+SWC*2));    //set pin for SWC to pull down
SW_input_port->PUPDR &= ~(1<<(SWC*2));	 	 //set pin for SWC to pull down
}
void config_SWD(void)  //config Switch D on PG 3
{
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;       //enable GPIOG
SW_input_port->MODER &= ~(1<<(SWD*2));     //Set switch D to input (00)
SW_input_port->MODER &= ~(1<<(1+(SWD*2))); //Set switch D to input (00)
SW_input_port->PUPDR |= (1<<(1+SWD*2));    //set pin for SWD to pull down
SW_input_port->PUPDR &= ~(1<<(SWD*2));	 	 //set pin for SWD to pull down
}

void config_buttons (void)   //use to configure all the switches and buttons
{
 config_Blue_Button(); //config Blue Button on PC 13
 config_SWA();         //config Switch A on PG 0
 config_SWB();         //config Switch B on PG 1
 config_SWC();         //config Switch C on PG 2
 config_SWD();	       //config Switch D on PG 3
}

int read_Blue_Button (void) //read BlueButton input; pressed (not0) or not pressed (0)
{
	int a;
	a= ((1<<BlueButton)&(BB_input_port->IDR)); //mask blue button pin and read it
	return a;	//return value, not 0 or 0
}

int read_SWA (void) //read SWA input; pressed (not0) or not pressed (0) 
{
	int a;
	a= ((1<<SWA)&(SW_input_port->IDR)); //mask SWA pin and read it
	return a;	//return value, not 0 or 0
}

int read_SWB (void) //read SWB input; pressed (not0) or not pressed (0) 
{
	int a;
	a= ((1<<SWB)&(SW_input_port->IDR)); //mask SWB pin and read it
	return a;	//return value, not 0 or 0
}
int read_SWC (void) //read SWC input; pressed (not0) or not pressed (0) 
{
	int a;
	a= ((1<<SWC)&(SW_input_port->IDR)); //mask SWC pin and read it
	return a;	//return value, not 0 or 0
}

int read_SWD (void)  //read SWD input; pressed (not0) or not pressed (0) 
{
	int a;
	a= ((1<<SWD)&(SW_input_port->IDR)); //mask SWD pin and read it
	return a;	//return value, not 0 or 0
}

void switches(void)   //function containing the code which control what the switches (A,B,C,D) do
{
		int A;         //create variable A for switch A
		A=read_SWA();  //A reads if switch A is pressed or not
	  int B;         //create variable B for switch B
		B=read_SWB();  //B reads if switch B is pressed or not
	  int C;         //create variable C for switch C
		C=read_SWC();  //C reads if switch C is pressed or not
	  int D;         //create variable D for switch D
		D=read_SWD();  //D reads if switch D is pressed or not
		
		
		
		if (A!=0)  //if A is pressed
		{
		 send_usart_string("Switch A pressed\n\r"); //display to USART that switch A has been pressed
     Init_Timer5_buzzer_A();                    //buzzer beeps
		 select_LINE(2);                            //navigates to 'A' on LCD DAC command line
	   putLCD_string("A");                        //navigates to 'A' on LCD DAC command line
		 cmdLCD(0x10);                              //navigates to 'A' on LCD DAC command line
     Init_Timer2_dac_square();                  //chooses DAC output relating to 'A'
		 output=1;						                      //chooses DAC output relating to 'A'
		 A=read_SWA();	                            //wait for switch A to be released
		 do                                         //wait for switch A to be released
		 {                                          //wait for switch A to be released  
		  A=read_SWA();	                            //wait for switch A to be released
		 }while (A!=0);	                            //wait for switch A to be released
		 Init_Timer5_buzzer_off_low();              //turn off buzzer beep
		}
				
		if (B!=0) //if B is pressed
		{
		 send_usart_string("Switch B pressed\n\r");	 //display to USART that switch B has been pressed
		 Init_Timer5_buzzer_A();                     //buzzer beeps				
		 select_LINE(2);	                           //navigates to 'B' on LCD DAC command line
		 putLCD_string("A B");                       //navigates to 'B' on LCD DAC command line
     cmdLCD(0x10);		                           //navigates to 'B' on LCD DAC command line
     Init_Timer2_dac_tri();	                     //chooses DAC output relating to 'B'
		 output=2;			                             //chooses DAC output relating to 'B'
		 B=read_SWB();                               //wait for switch B to be released  
		 do                                          //wait for switch B to be released
		 {                                           //wait for switch B to be released
		  B=read_SWB();	                             //wait for switch B to be released
		 }while (B!=0);	                             //wait for switch B to be released
		 Init_Timer5_buzzer_off_low();               //turn off buzzer beep
    }
		
		if (C!=0) //if C is pressed
		{
		 send_usart_string("Switch C pressed\n\r"); //display to USART that switch C has been pressed
		 Init_Timer5_buzzer_A();	                  //buzzer beeps		
		 select_LINE(2);                            //navigates to 'C' on LCD DAC command line
		 putLCD_string("A B C");                    //navigates to 'C' on LCD DAC command line  
		 cmdLCD(0x10);	                            //navigates to 'C' on LCD DAC command line
		 Init_Timer2_dac_sin();	                    //chooses DAC output relating to 'C' 
		 output=3;	                                //chooses DAC output relating to 'C'
		 C=read_SWC();                              //wait for switch C to be released	
		 do                                         //wait for switch C to be released 
		 {                                          //wait for switch C to be released
		  C=read_SWC();	                            //wait for switch C to be released
		 }while (C!=0);		                          //wait for switch C to be released
		 Init_Timer5_buzzer_off_low();              //turn off buzzer beep
		}
	
		if (D!=0)  //if D is pressed
		{
		 send_usart_string("Switch D pressed\n\r"); //display to USART that switch D has been pressed
		 Init_Timer5_buzzer_A();                    //buzzer beeps
		 select_LINE(2);	                          //navigates to 'D' on LCD DAC command line
		 putLCD_string("A B C D");                  //navigates to 'D' on LCD DAC command line
		 cmdLCD(0x10);	                            //navigates to 'D' on LCD DAC command line
		 output=4;		                              //chooses DAC output relating to 'D'
		 D=read_SWD();	                            //wait for switch D to be released
		 do                                         //wait for switch D to be released
		 {                                          //wait for switch D to be released
		  D=read_SWD();	                            //wait for switch D to be released
		 }while (D!=0);	                            //wait for switch D to be released
     Init_Timer5_buzzer_off_low();		          //turn off buzzer beep
		} 
}	