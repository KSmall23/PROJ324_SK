#include "usart.h"
#include "lcd.h"
#include "timers.h"
#include "ADC.h"
#include "DAC.h"

unsigned int output;        //global variable to choose output for DACs
unsigned int tune_choice=1; //global vairable to choose which tune to be played on buzzer
unsigned int play_tune=0;   //global variable to choose to play a tune



int fputc(int ch, FILE *f) //allows printf to print string to USART and LCD
{
	send_usart (ch); //lets printf print to USART
	putLCD (ch);     //lets printf print to LCD
	return ch;		
}


int fgetc(FILE *f) //allows getchar to get data from USART
{
	while (! (USART_MODULE->SR & USART_SR_RXNE )); //read data Register full?
	int ch = USART_MODULE->DR;
	return ch;
}

int USART3_GetData(void) //gets data from USART
{
  if (USART3->SR & USART_SR_RXNE ) //read data Register full?
  {
   return USART3->DR; //return data
  }
  else return -1; 
}

void send_usart(unsigned char d) //sends one character to USART
{
	while(!(USART_MODULE->SR & USART_SR_TC)); 
	USART_MODULE->DR=d;												//write byte to usart data register
}

void init_USART(void) //configs USART
{
	unsigned char i1,i2;
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;		//usart port clock enable
	
	USART_PORT->MODER&=~(										//clear pin function bits
		(3u<<(2*USART_TX_pin))
		|(3u<<(2*USART_RX_pin))
			);
	USART_PORT->MODER|=(										//reset pin function bits (alternate function)
		(2u<<(2*USART_TX_pin))
		|(2u<<(2*USART_RX_pin))
			);
	
	i1=USART_TX_pin/8;											// used to select AFR[reg] for TX_pin ... pins 0-7 AFR[0] pins 8-15 AFR[1]
	i2=USART_RX_pin>>3;											// same as above for RX_pin (uses shift to divide)

		// ALTERNATE FUNCTION SELECT BITS
	USART_PORT->AFR[i1]&=~(0x0f<<(4*(USART_TX_pin-(i1*8))));    //clear pin function
	USART_PORT->AFR[i1]|=(0x07<<(4*(USART_TX_pin-(i1*8))));			// set usart as alternate function for TX_pin
	USART_PORT->AFR[i2]&=~(0x0f<<(4*(USART_RX_pin-(i2*8))));		// clear pin function
	USART_PORT->AFR[i2]|=(0x07<<(4*(USART_RX_pin-(i2*8))));			//set usart as alternate function for RX_pin
	
	RCC->APB1ENR|=RCC_APB1ENR_USART3EN;			//usart clock enable
	USART_MODULE->CR1|=(										//USART CONFIG
			USART_CR1_TE												//transmit enable
			|USART_CR1_RE												//receive enable
			|USART_CR1_UE												//usart main enable bit
			|USART_CR1_RXNEIE                   //USART3 interrupt enable
				);

    USART_MODULE ->BRR=0xc3;	                       //SET BAUD RATE at 230400b/s FOR 180Mhz CLOCK																						
	  USART_Interrupt_Enable();							          //Enable global intterupt																	
																									
}
void send_usart_string(const char *d) //send string to USART
{ 
	unsigned int a;        //create variable for count through string
	a=0;                   //set count to 0
	while(d[a] != ('\0'))  //string ends with 0, so will send each byte until it hits \0
	{
		send_usart(d[a]);    //send each byte to terminal
		a++;                 //increment count
	}
												
}

void USART_Interrupt_Enable(void) //enables USART3 interrupt
{
	NVIC->ISER[USART3_IRQn>>5]|=(1<<(USART3_IRQn & 0x1F)); //enables interrupt in register
}

void USART3_IRQHandler (void) //USART3 INTERRUPT SERVICE ROUTINE happens whenever anything is typed in USART terminal
{
 send_usart(0x1B);                 //ANSII escape code to move cursor left two columns
 send_usart_string("[2D\r");       //ANSII escape code to move cursor left two columns

	int abcd;                        //create variable where whats recieved from the USART will be stored
	abcd=USART3_GetData();           //read the character inputted from USART when typed
	
	if ((abcd == 'a') | (abcd=='A')) // A in lowercase or uppercase, if an A is typed in will change the DAC2 output to 8kHz square wave
	{
		Init_Timer2_dac_square();  
		output=1;	
	}	
	if ((abcd == 'b') | (abcd=='B')) // B in lowercase or uppercase, if a B is typed in will change the DAC2 output to 4kHz Triangle wave
	{  		
		Init_Timer2_dac_tri();
		output=2;	
	}	
	if ((abcd == 'c') | (abcd=='C')) // C in lowercase or uppercase, if a C is typed in will change the DAC2 output to 2kHz sine wave
	{
  	Init_Timer2_dac_sin();
		output=3;	
	}	
	if ((abcd == 'd') | (abcd=='D')) // D in lowercase or uppercase, if a D is typed in will change the DAC2 output to onboard mic voltage level
	{
		output=4;
	}
	
	
	if (abcd =='1')                  //if 1 is typed in will play tune_1 on buzzer
	{
	tune_choice=1;
  play_tune=1;		
  }
  if (abcd =='2')                  //if 2 is typed in will play tune_2 on buzzer
	{
	tune_choice=2;
  play_tune=1;		
  }	
  USART_MODULE -> DR &= ~(1<<USART_RXNE_pin); //reset flag
}


  
