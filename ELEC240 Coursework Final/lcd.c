#include <stm32f4xx.h>
#include "lcd.h"
#include "Delay.c"

void lcd_delayus(unsigned int us)		//blocking delay for LCD, argument is approximate number of micro-seconds to delay
{
	unsigned char i;
	while(us--)
	{
		for(i=0; i<SystemCoreClock/4000000; i++){__NOP();}
	}
}

void WaitLcdBusy(void) //wait for LCD to not be busy
{
		int busy; //create variable 'busy' to test whether LCD is Busy of not
  do
	{
		set_LCD_bus_input(); //set LCD to input to read
  	set_LCD_RW(); //set read/write line
  	clr_LCD_RS(); //clear register select
  	set_LCD_E();  //set enable line
		WaiT3(1);     //wait short time
  	busy= LCD_PORT->IDR; //busy = bit 7 (busy flag) 1 if busy, 0 if not
  	busy &=(1<<7);       //busy = bit 7 (busy flag) 1 if busy, 0 if not
	  clr_LCD_E(); //slear enable line
 	} while(busy>0);  //wait for LCD to not be busy
	set_LCD_bus_output(); //set LCD back to output to send data
}

void set_LCD_data(unsigned char d) //set data on LCD data bus lines
{
	LCD_PORT->BSRR=(0xff<<(LCD_D0_pin+16));	//clear data lines
	LCD_PORT->BSRR=(d<<LCD_D0_pin);					//put data on lines
}

void LCD_strobe(void)		//10us high pulse on LCD enable line
{
	lcd_delayus(10);  //wait short tme
	set_LCD_E();      //turn on enable LCD line
	lcd_delayus(10);  //wait short time
	clr_LCD_E();      //turn off enable LCD line
}


void cmdLCD(unsigned char cmd)		//sends a byte to the LCD control register
{
	WaitLcdBusy();				//wait for LCD to be not busy
	clr_LCD_RS();					//control command
	clr_LCD_RW();					//write command
	set_LCD_data(cmd);		//set data on bus
	LCD_strobe();					//apply command
}

void putLCD(unsigned char put)	//sends a char to the LCD display
{
	WaitLcdBusy();				//wait for LCD to be not busy
	set_LCD_RS();					//text command
	clr_LCD_RW();					//write command
	set_LCD_data(put);		//set data on bus
	LCD_strobe();					//apply command
}

void putLCD_string(const char *put) //sends string to LCD display
{ 
	unsigned int a=0;        //create variable to counter through string
	while(put[a] != ('\0'))  //string ends with 0, so will send each byte until it hits \0
	{
		putLCD(put[a]);        //send each byte to terminal
		a++;                   //increment counter
	};											
}
void clear_LCD (void) //clears LCD using MACRO 
{
	LCD_CLR();
}	
void select_LINE (int a) //selects which line to write to on LCD
{
  if (a<2)  //if 1 (less than 2)
   { 
	  cmdLCD(LCD_LINE1); //write to line 1
   }
   else if (a>1) //if 2 (greater than 1)
   {
    cmdLCD(LCD_LINE2); //write to line 2
   };	
}

void initLCD(void) //config LCD for 8 Bit Mode
{
		SystemCoreClockUpdate();
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;	//enable LCD port clock
	
	
			//CONFIG LCD GPIO PINS
		LCD_PORT->MODER&=~(					//clear pin direction settings
			(3u<<(2*LCD_RS_pin))
			|(3u<<(2*LCD_RW_pin))
			|(3u<<(2*LCD_E_pin))
			|(0xffff<<(2*LCD_D0_pin))
			);
	
	
	LCD_PORT->MODER|=(				//reset pin direction settings to digital outputs
			(1u<<(2*LCD_RS_pin))
			|(1u<<(2*LCD_RW_pin))
			|(1u<<(2*LCD_E_pin))
			|(0x5555<<(2*LCD_D0_pin))
		);

	
			//LCD INIT COMMANDS
	clr_LCD_RS();					//all lines default low
	clr_LCD_RW();
	clr_LCD_E();
	
	lcd_delayus(25000);		//25ms startup delay
	cmdLCD(0x38);	        //Function set: 2 Line, 8-bit, 5x7 dots
	cmdLCD(0x0f);	        //Display on, Cursor blinking command
	cmdLCD(0x01);	        //Clear LCD
	cmdLCD(0x06);	        //Entry mode, auto increment with no shift
}

int GetLCDdata(void) //gets gata from LCD
{
		int data;      
 
		set_LCD_bus_input();
  	set_LCD_RW();
  	clr_LCD_RS();
  	set_LCD_E();
		WaiT3(1);
  	data= (LCD_PORT->IDR & (1<<5));
	  clr_LCD_E();
 
	set_LCD_bus_output();
	return data;
}


