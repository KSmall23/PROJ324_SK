#ifndef __LED_H_
#define __LED_H_
#include "stm32f4xx.h"

#define Blinky_Green 0
#define Blinky_Red 14
#define Blinky_Blue 7

#define Traf_Red1 2
#define Traf_Red2 7
#define Traf_Yellow1 3
#define Traf_Yellow2 8
#define Traf_Green1 6
#define Traf_Green2 9
#define Traf_White 10

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

#define GPIOC_led_on_PushPull(x) ((GPIOC->BSRR) = (1<<x))         //call red1, green1 or yellow1 lights to turn on: Push-pull
#define GPIOC_led_off_PushPull(x) ((GPIOC->BSRR) = (1<<(16+x)))   //call red1, green1 or yellow1 lights to turn off: Push-pull
#define GPIOC_led_on_OpenDrain(x) ((GPIOC->BSRR) = (1<<(16+x)))   //call red2, green2 or yellow2 lights to turn on: Open drain
#define GPIOC_led_off_OpenDrain(x) ((GPIOC->BSRR) = (1<<x))       //call red2, green2 or yellow2 lights to turn off: Open drain
#define white_led_on ((GPIOF->BSRR) = (1<<(16+Traf_White)))             //call white led (green man) to turn on
#define white_led_off ((GPIOF->BSRR) = (1<<Traf_White))                 //call white led (green man) to turn off
#define GPIOB_led_on(x) ((GPIOB->BSRR) = (1<<x))                  //call blinky lights to turn on
#define GPIOB_led_off(x) ((GPIOB->BSRR) = (1<<(16+x)))            //call blinky lights to turn off
#define clear_led_bus (GPIOE->BSRR) = (0xff<<(16+2))              //clear all bits on led data bus for LED bars and 7seg display 

void config_TRAF_RED1 (void);      //set up first red light on support board on GPIOC
void config_TRAF_YELLOW1 (void);   //set up first yellow light on support board on GPIOC 
void config_TRAF_GREEN1 (void);    //set up first green light on support board on GPIOC
void config_TRAF_RED2 (void);      //set up second red light on support board on GPIOC
void config_TRAF_YELLOW2 (void);   //set up second yellow light on support board on GPIOC
void config_TRAF_GREEN2 (void);    //set up second green light on support board on GPIOC
void config_TRAF_WHITE (void);     //set up white light on support board on GPIOF
void config_Blinky_Green (void);   //set up green light on MCU
void config_Blinky_Red (void);     //set up red light on MCU 
void config_Blinky_Blue (void);    //set up blue light on MCU
void config_Bars (void);           //set up bar lights on support board
void config_latch_leds (void);     //set up LED bus lights
void config_7seg (void);           //set up 7-segment display on support board
void config_Lights (void);         //set up all of the LEDs

void toggle_Blinky_Red (void);     //flips Blinky_Red light to opposite state to previous
void toggle_Blinky_Green (void);   //flips Blinky_Green light to opposite state to previous
void toggle_Blinky_Blue (void);    //flips Blinky_Blue light to opposite state to previous
void toggle_TRAF_RED1 (void);      //flips TRAF_RED1 light to opposite state to previous
void toggle_TRAF_YELLOW1 (void);   //flips TRAF_YELLOW1 light to opposite state to previous
void toggle_TRAF_GREEN1 (void);    //flips TRAF_GREEN1 light to opposite state to previous
void toggle_TRAF_RED2 (void);      //flips TRAF_RED2 light to opposite state to previous  
void toggle_TRAF_YELLOW2 (void);   //flips TRAF_YELLOW2 light to opposite state to previous
void toggle_TRAF_GREEN2 (void);    //flips TRAF_GREEN2 light to opposite state to previous
void toggle_TRAF_WHITE (void);     //flips TRAF_WHITE light to opposite state to previous 

void traf_pause (void); //puts traffic lights so that red is on for both of them (for pedestrian crossing)

#endif
