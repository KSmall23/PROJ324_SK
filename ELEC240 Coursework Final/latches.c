#include "latches.h"



void strobe_BlueBar (void) //turn latch enable on and then off to set bits on blue bar
{
   WaiT3(1);                           //short wait
	 GPIOE->BSRR = (1<<BlueBar_LE);      //turn on BlueBar latch enable
	 WaiT3(1);                           //short wait
	 GPIOE->BSRR =1<<(16+BlueBar_LE);    //turn off BlueBar latch enable
}

void strobe_RedBar (void) //turn latch enable on and then off to set bits on red bar
{ 
   WaiT3(1);                           //short wait
	 GPIOE->BSRR = (1<<RedBar_LE);       //turn on RedBar latch enable
	 WaiT3(1);                           //short wait
	 GPIOE->BSRR =1<<(16+RedBar_LE);     //turn off RedBar latch enable
}

void strobe_GreenBar (void) //turn latch enable on and then off to set bits on green bar
{
   WaiT3(1);                           //short wait
	 GPIOE->BSRR = (1<<GreenBar_LE);     //turn on GreenBar latch enable 
	 WaiT3(1);                           //short wait
	 GPIOE->BSRR =1<<(16+GreenBar_LE);   //turn off GreenBar latch enable
}

void strobe_Seg1 (void) //turn latch enable on and then off to set bits on 1st digit
{
   WaiT3(1);                           //short wait  
	 GPIOE->BSRR = (1<<Seg1_LE);         //turn on Seg1 latch enable
	 WaiT3(1);                           //short wait
	 GPIOE->BSRR =1<<(16+Seg1_LE);       //turn off Seg1 latch enable 
}

void strobe_Seg2 (void) //turn latch enable on and then off to set bits on 2nd digit
{
   WaiT3(1);                           //short wait
	 GPIOE->BSRR = (1<<Seg2_LE);         //turn on Seg2 latch enable
	 WaiT3(1);                           //short wait
	 GPIOE->BSRR =1<<(16+Seg2_LE);       //turn off Seg2 latch enable
}

void BlueBar_Voltage (double a) //puts number of leds on blue bar for comparison of voltage level on POT	
{
if (a>3.000) //if the reading from the POT is higher than 3, all leds on
		 {
			clear_led_bus;
			GPIOE->BSRR =	(0b11111111<<(2));
	    strobe_BlueBar();
     }
		if ((a<3.000)&(a>2.625)) //if the reading from the POT is higher than 2.625 but lower than 3, 7 leds on
		 {
			clear_led_bus;
			GPIOE->BSRR =	(0b01111111<<(2));
	    strobe_BlueBar();
		 }
		
		if ((a<2.625)&(a>2.250)) //if the reading from the POT is higher than 2.250 but lower than 2.625, 6 leds on
		 {
			clear_led_bus;
			GPIOE->BSRR =	(0b00111111<<(2));
	    strobe_BlueBar();
	  	}
		
		if ((a<2.250)&(a>1.875)) //if the reading from the POT is higher than 1.875 but lower than 2.250, 5 leds on
		 {
			clear_led_bus;
			GPIOE->BSRR =	(0b00011111<<(2));
	    strobe_BlueBar();
	  	}
		
		if ((a<1.875)&(a>1.500)) //if the reading from the POT is higher than 1.500 but lower than 1.875, 4 leds on
		 {
		 	clear_led_bus;
			GPIOE->BSRR =	(0b00001111<<(2));
	    strobe_BlueBar();
		 }

		if ((a<1.500)&(a>1.125)) //if the reading from the POT is higher than 1.125 but lower than 1.500, 3 leds on
		 {
			clear_led_bus;
			GPIOE->BSRR =	(0b00000111<<(2));
	    strobe_BlueBar();
		 }		
		
		if ((a<1.125)&(a>0.750)) //if the reading from the POT is higher than 0.750 but lower than 1.125, 2 leds on
		 {
			clear_led_bus;
			GPIOE->BSRR =	(0b00000011<<(2));
	    strobe_BlueBar();
		 }
		if ((a<0.750)&(a>0.375)) //if the reading from the POT is higher than 0.375 but lower than 0.750, 1 led on
		 {
			clear_led_bus;
			GPIOE->BSRR =	(0b00000001<<(2));
	    strobe_BlueBar();

		 }
		if (a<0.375) //if POT reading less than 0.375, all leds off
		 {
         clear_led_bus;
	       strobe_BlueBar();		
		 }

}


void GreenBar_Voltage (double a) //puts number of leds on blue bar for comparison of voltage level on LDR	
{
if (a>2.700) //if LDR reading more than 2.700, all leds on 
		 {
			clear_led_bus;
			GPIOE->BSRR =	(0b11111111<<(2));
	    strobe_GreenBar();
     }
		if ((a<2.700)&(a>2.365)) //if the reading from the LDR is higher than 2.365 but lower than 2.700, 7 leds on
		 {
			clear_led_bus;
			GPIOE->BSRR =	(0b01111111<<(2));
	    strobe_GreenBar();
		 }
		
		if ((a<2.365)&(a>2.030)) //if the reading from the LDR is higher than 2.030 but lower than 2.365, 6 leds on
		 {
			clear_led_bus;
			GPIOE->BSRR =	(0b00111111<<(2));
	    strobe_GreenBar();
	  	}
		
		if ((a<2.030)&(a>1.695)) //if the reading from the LDR is higher than 1.695 but lower than 2.030, 5 leds on
		 {
			clear_led_bus;
			GPIOE->BSRR =	(0b00011111<<(2));
	    strobe_GreenBar();
	  	}
		
		if ((a<1.695)&(a>1.360)) //if the reading from the LDR is higher than 1.360 but lower than 1.695, 4 leds on 
		 {
		 	clear_led_bus;
			GPIOE->BSRR =	(0b00001111<<(2));
	    strobe_GreenBar();
		 }

		if ((a<1.360)&(a>1.025)) //if the reading from the LDR is higher than 1.025 but lower than 1.360, 3 leds on
		 {
			clear_led_bus;
			GPIOE->BSRR =	(0b00000111<<(2));
	    strobe_GreenBar();
		 }		
		
		if ((a<1.025)&(a>0.690)) //if the reading from the LDR is higher than 0.690 but lower than 1.025, 2 leds on
		 {
			clear_led_bus;
			GPIOE->BSRR =	(0b00000011<<(2));
	    strobe_GreenBar();
		 }
		if ((a<0.690)&(a>0.355)) //if the reading from the LDR is higher than 0.355 but lower than 0.690, 1 led on
		 {
			clear_led_bus;
			GPIOE->BSRR =	(0b00000001<<(2));
	    strobe_GreenBar();

		 }
		if (a<0.355) //if LDR reading less than 0.355, all leds off
		 {
         clear_led_bus;
	       strobe_GreenBar();		
		 }

}

void RedBar_Voltage (double a) //puts number of leds on blue bar for comparison of voltage level on MIC	
{
if (a>3.250) //if MIC reading more than 3.250, all leds on 
		 {
			clear_led_bus;
			GPIOE->BSRR =	(0b11111111<<(2));
	    strobe_RedBar();
     }
		if ((a<3.250)&(a>3.000)) //if the reading from the MIC is higher than 3.000 but lower than 3.250, 7 leds on
		 {
			clear_led_bus;
			GPIOE->BSRR =	(0b01111111<<(2));
	    strobe_RedBar();
		 }
		
		if ((a<3.000)&(a>2.750)) //if the reading from the MIC is higher than 2.750 but lower than 3.000, 6 leds on
		 {
			clear_led_bus;
			GPIOE->BSRR =	(0b00111111<<(2));
	    strobe_RedBar();
	  	}
		
		if ((a<2.750)&(a>2.250)) //if the reading from the MIC is higher than 2.250 but lower than 2.750, 5 leds on
		 {
			clear_led_bus;
			GPIOE->BSRR =	(0b00011111<<(2));
	    strobe_RedBar();
	  	}
		
		if ((a<2.250)&(a>2.000)) //if the reading from the MIC is higher than 2.000 but lower than 2.250, 4 leds on
		 {
		 	clear_led_bus;
			GPIOE->BSRR =	(0b00001111<<(2));
	    strobe_RedBar();
		 }

		if ((a<2.000)&(a>1.750)) //if the reading from the MIC is higher than 1.750 but lower than 2.000, 3 leds on
		 {
			clear_led_bus;
			GPIOE->BSRR =	(0b00000111<<(2));
	    strobe_RedBar();
		 }		
		
		if ((a<1.750)&(a>1.500)) //if the reading from the MIC is higher than 1.500 but lower than 1.750, 2 leds on
		 {
			clear_led_bus;
			GPIOE->BSRR =	(0b00000011<<(2));
	    strobe_RedBar();
		 }
		if ((a<1.500)&(a>1.250)) //if the reading from the MIC is higher than 1.250 but lower than 1.500, 1 led on
		 {
			clear_led_bus;
			GPIOE->BSRR =	(0b00000001<<(2));
	    strobe_RedBar();

		 }
		if (a<1.250) //if MIC reading less than 1.250, all leds off
		 {
         clear_led_bus;
	       strobe_RedBar();		
		 }

}