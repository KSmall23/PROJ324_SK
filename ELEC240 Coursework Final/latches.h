#ifndef _LATCHES_H_
#define _LATCHES_H_
#include <stm32f429xx.h>


#define Bar_OE 0
#define RedBar_LE 12
#define GreenBar_LE 13
#define BlueBar_LE 14
#define Seg_OE 15
#define Seg1_LE 10
#define Seg2_LE 11

#define led_D0 2
#define led_D1 3
#define led_D2 4
#define led_D3 5
#define led_D4 6
#define led_D5 7
#define led_D6 8
#define led_D7 9

#define clear_led_bus (GPIOE->BSRR) = (0xff<<(16+2))              //clear all bits on led data bus for LED bars and 7seg display 

void strobe_BlueBar (void); //turn latch enable on and then off to set bits on blue bar
void strobe_RedBar (void); //turn latch enable on and then off to set bits on red bar
void strobe_GreenBar (void); //turn latch enable on and then off to set bits on green bar
void strobe_Seg1 (void); //turn latch enable on and then off to set bits on 1st digit
void strobe_Seg2 (void); //turn latch enable on and then off to set bits on 2nd digit	

void BlueBar_Voltage (double a); //puts number of leds on blue bar for comparison of voltage level on POT
void GreenBar_Voltage (double a); //puts number of leds on blue bar for comparison of voltage level on LDR	
void RedBar_Voltage (double a); //puts number of leds on blue bar for comparison of voltage level on MIC	



#endif
