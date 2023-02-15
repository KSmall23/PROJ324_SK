#ifndef _BUTTONS_H
#define _BUTTONS_H
#include <stm32f4xx.h>

#define BlueButton 13
#define SWA 0
#define SWB 1
#define SWC 2
#define SWD 3
#define SW_input_port GPIOG
#define BB_input_port GPIOC

void config_Blue_Button(void); //Set up Blue Button on PC 13 to input
void config_SWA(void);         //Set up SWA on PG 0 to input
void config_SWB(void);         //Set up SWB on PG 1 to input 
void config_SWC(void);         //Set up SWC on PG 2 to input
void config_SWD(void);         //Set up SWD on PG 3 to input
void config_buttons(void);     //Set up all swtiches and buttons to input

int read_Blue_Button (void);   //read BlueButton input; pressed (not0) or not pressed (0)
int read_SWA (void);           //read SWA input; pressed (not0) or not pressed (0)
int read_SWB (void);           //read SWB input; pressed (not0) or not pressed (0)
int read_SWC (void);           //read SWC input; pressed (not0) or not pressed (0)
int read_SWD (void);           //read SWD input; pressed (not0) or not pressed (0)	

void switches(void);           //function containing the code which control what the switches (A,B,C,D) do

#endif
