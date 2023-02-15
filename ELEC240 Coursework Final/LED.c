#include "LED.h"
#include "Delay.h"

void config_Lights (void)  //config all LEDS on Nucleo and Module support board
{
	config_Blinky_Green();  //config green led on Nucleo board
	config_Blinky_Red();    //config red led on Nucleo board
	config_Blinky_Blue();   //config blue led on Nucleo board
	config_TRAF_RED1();     //config Red led for traffic light 1
	config_TRAF_YELLOW1();  //config Yellow led for traffic light 1
	config_TRAF_GREEN1();   //config Green led for traffic light 1   
	config_TRAF_RED2();     //config Red led for traffic light 2
	config_TRAF_YELLOW2();  //config Yellow led for traffic light 2  
	config_TRAF_GREEN2();   //config Green led for traffic light 2
	config_TRAF_WHITE();    //config White led for green man of traffic lights
	config_Bars();          //config OE for LED bar latches
	config_7seg();          //config OE and LEs for 7segment display
	config_latch_leds ();   //config led bus for Bars and 7seg display
}
void config_Blinky_Green (void) //config green led on Nucleo board
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;             //enable GPIOB
	GPIOB->MODER |= (1<<(Blinky_Green*2));           //set pin0 to output (01)
	GPIOB->MODER &= ~(1<<(1+Blinky_Green*2));        //set pin0 to output (01)
	GPIOB->OTYPER&= ~(1<<Blinky_Green);              //set pin0 type to push-pull 
	GPIOB->ODR &= ~(1<<Blinky_Green);                //Make sure LED starts OFF
}
void config_Blinky_Red (void)  //config red led on Nucleo board
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;             //enable GPIOB
	GPIOB->MODER |= (1<<(Blinky_Red*2));           //set pin7 to output (01)
	GPIOB->MODER &= ~(1<<(1+Blinky_Red*2));        //set pin7 to output (01)
	GPIOB->OTYPER&= ~(1<<Blinky_Red);              //set pin7 type to push-pull 
	GPIOB->ODR &= ~(1<<Blinky_Red);                //Make sure LED starts OFF
}
void config_Blinky_Blue (void) //config blue led on Nucleo board
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;             //enable GPIOB
	GPIOB->MODER |= (1<<(Blinky_Blue*2));           //set pin7 to output (01)
	GPIOB->MODER &= ~(1<<(1+Blinky_Blue*2));        //set pin7 to output (01)
	GPIOB->OTYPER&= ~(1<<Blinky_Blue);              //set pin7 type to push-pull 
	GPIOB->ODR &= ~(1<<Blinky_Blue);                //Make sure LED starts OFF
}
void config_Bars (void) //config OE for LED bar latches
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;              //enable GPIOE
	GPIOE->MODER |= (1<<(Bar_OE*2));                  //set LED bar output enable to output      
	GPIOE->MODER &= ~(1<<(1+Bar_OE*2));               //set LED bar output enable to output  
	GPIOE->OTYPER &= ~(1<<Bar_OE);                    //set output enable type to open drain 	
	GPIOE->ODR &= ~(1<<Bar_OE);                       //turn output enable on and so pin to 0 (~OE = output enable on)                           
}

void config_latch_leds (void) //config led bus for Bars and 7seg display
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;              //enable GPIOE

  GPIOE->MODER |= (1<<(led_D0*2))|(1<<(led_D1*2))|(1<<(led_D2*2))|(1<<(led_D3*2))|(1<<(led_D4*2));                  //set all pins on latches for bars to output
	GPIOE->MODER |= (1<<(led_D5*2))|(1<<(led_D6*2))|(1<<(led_D7*2));                                                  //set all pins on latches for bars to output  
	GPIOE->MODER &= ~((1<<(1+led_D0*2))|(1<<(1+led_D1*2))| (1<<(1+led_D2*2))|(1<<(1+led_D3*2))| (1<<(1+led_D4*2)));   //set all pins on latches for bars to output
	GPIOE->MODER &= ~((1<<(1+led_D5*2))| (1<<(1+led_D6*2))|(1<<(1+led_D7*2)));                                        //set all pins on latches for bars to output
	
	GPIOE->MODER |=  (1<<(RedBar_LE*2))|(1<<(GreenBar_LE*2))|(1<<(BlueBar_LE*2));                                     //set led bar latch enable to output
	GPIOE->MODER &= ~(1<<(1+RedBar_LE*2))|(1<<(1+GreenBar_LE*2))| (1<<(1+BlueBar_LE*2));                              //set led bar latch enable to output

	GPIOE->OTYPER &= ~((1<<led_D0)|(1<<led_D1)|(1<<led_D2)|(1<<led_D3)|(1<<led_D4));                                  //set led pins to push-pull
  GPIOE->OTYPER &= ~((1<<led_D5)|(1<<led_D6)|(1<<led_D7));                                                          //set led pins to push-pull
	
	GPIOE->OTYPER &= ~(1<<RedBar_LE);                                                                                 //set latch enable type to push-pull
	GPIOE->OTYPER &= ~(1<<GreenBar_LE);                                                                               //set latch enable type to push-pull
	GPIOE->OTYPER &= ~(1<<BlueBar_LE);                                                                                //set latch enable type to push-pull
  	
	GPIOE->ODR &= ~((1<<led_D0)|(1<<led_D1)|(1<<led_D2)|(1<<led_D3)|(1<<led_D4));                                     //make sure LEDs start off
  GPIOE->ODR &= ~((1<<led_D5)|(1<<led_D6)|(1<<led_D7));	                                                            //make sure LEDs start off     
	
	GPIOE->ODR &= ~((1<<RedBar_LE) | (1<<GreenBar_LE) | (1<<BlueBar_LE));                                             //turn latch enables off 
}	


void config_7seg (void) //config OE and LEs for 7segment display
{
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;                                      //enable GPIOE 
GPIOE->MODER |=(1<<Seg_OE*2) |(1<<Seg1_LE*2)|(1<<11*2);                   //set 7seg Output and Latch enable to output
GPIOE->MODER&= ~((1<<(1+Seg_OE*2))|(1<<(1+Seg1_LE*2))|(1<<(1+Seg2_LE*2)));//set 7seg Output and Latch enable to output	
}

void config_TRAF_RED1 (void)  //config Red led for traffic light 1
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;             //enable GPIOC
	GPIOC->MODER |= (1<<(Traf_Red1*2));              //set pin2 to output (01)
	GPIOC->MODER &= ~(1<<(1+Traf_Red1*2));           //set pin2 to output (01)
	GPIOC->OTYPER&= ~(1<<Traf_Red1);                 //set pin2 type to push-pull 
	GPIOC->ODR &= ~(1<<Traf_Red1);                   //Make sure LED starts OFF
}

void config_TRAF_YELLOW1 (void) //config Yellow led for traffic light 1
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; //enable GPIOC
	GPIOC->MODER |= (1<<(Traf_Yellow1*2));              //set pin3 to output (01)
	GPIOC->MODER &= ~(1<<(1+Traf_Yellow1*2));           //set pin3 to output  (01)
	GPIOC->OTYPER&= ~(1<<Traf_Yellow1);                 //set pin3 type to push-pull
	GPIOC->ODR &= ~(1<<Traf_Yellow1);                   //Make sure LED starts OFF
}

void config_TRAF_GREEN1 (void) //config Green led for traffic light 1
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; //enable GPIOC
	GPIOC->MODER |= (1<<(Traf_Green1*2));               //set pin6 to output (01)
	GPIOC->MODER &= ~(1<<(1+Traf_Green1*2));            //set pin6 to output (01)
	GPIOC->OTYPER&= ~(1<<Traf_Green1);                  //set pin6 type to push-pull
	GPIOC->ODR &= ~(1<<Traf_Green1);                    //Make sure LED starts OFF
}
void config_TRAF_RED2 (void) //config Red led for traffic light 2
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;                //enagble GPIOC
	GPIOC->MODER |= (1<<(Traf_Red2*2));                 //set pin7 to output (01)
	GPIOC->MODER &= ~(1<<(1+Traf_Red2*2));              //set pin7 to output (01)
	GPIOC->OTYPER|= (1<<Traf_Red2);                     //set pin7 type to open drain 
	GPIOC->ODR |= (1<<Traf_Red2);                       //Make sure LED starts OFF
}

void config_TRAF_YELLOW2 (void) //config Yellow led for traffic light 2
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;                //enable GPIOC
	GPIOC->MODER |= (1<<(Traf_Yellow2*2));              //set pin8 to output (01)
	GPIOC->MODER &= ~(1<<(1+Traf_Yellow2*2));           //set pin8 to output  (01)
	GPIOC->OTYPER|= (1<<Traf_Yellow2);                  //set pin8 type to open drain
	GPIOC->ODR |= (1<<Traf_Yellow2);                    //Make sure LED starts OFF
}

void config_TRAF_GREEN2 (void) //config Green led for traffic light 2
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;                //enable GPIOC
	GPIOC->MODER |= (1<<(Traf_Green2*2));               //set pin9 to output (01)
	GPIOC->MODER &= ~(1<<(1+Traf_Green2*2));            //set pin9 to output (01)
	GPIOC->OTYPER|= (1<<Traf_Green2);                   //set pin9 type to open drain
	GPIOC->ODR |= (1<<Traf_Green2);                     //Make sure LED starts OFF
}

void config_TRAF_WHITE (void) //config White led for green man of traffic lights
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;                //enable GPIOF
	GPIOF->MODER |= (1<<(Traf_White*2));                //set pin10 to output (01)
	GPIOF->MODER &= ~(1<<(1+Traf_White*2));             //set pin10 to output (01)
	GPIOF->OTYPER|= (1<<Traf_White);                    //set pin10 type to open drain
	GPIOF->ODR |= (1<<Traf_White);                      //Make sure LED starts OFF
}
void toggle_Blinky_Red (void) //change red on nucleo board to opposite state (on or off) than previous 
{
	GPIOB->ODR ^= (1<<Blinky_Red);  //toggle pin14
}
void toggle_Blinky_Green (void) //change green on nucleo board to opposite state (on or off) than previous 
{
	GPIOB->ODR ^= (1<<Blinky_Green);  //toggle pin0
}
void toggle_Blinky_Blue (void) //change blue on nucleo board to opposite state (on or off) than previous 
{
	GPIOB->ODR ^= (1<<Blinky_Blue);  //toggle pin7
}

void toggle_TRAF_RED1 (void) //change red for traffic light 1 to opposite state (on or off) than previous 
{
	GPIOC->ODR ^= (1<<Traf_Red1); //toggle pin2
}

void toggle_TRAF_YELLOW1 (void) //change yellow for traffic light 1 to opposite state (on or off) than previous 
{
	GPIOC->ODR ^= (1<<Traf_Yellow1); //toggle pin3
}

void toggle_TRAF_GREEN1 (void) //change green for traffic light 1 to opposite state (on or off) than previous 
{
	GPIOC->ODR ^= (1<<Traf_Green1); //toggle pin6
}

void toggle_TRAF_RED2 (void) //change red for traffic light 2 to opposite state (on or off) than previous 
{
	GPIOC->ODR ^= (1<<Traf_Red2); //toggle pin7
}

void toggle_TRAF_YELLOW2 (void) //change yellow for traffic light 2 to opposite state (on or off) than previous 
{
	GPIOC->ODR ^= (1<<Traf_Yellow2); //toggle pin8
}

void toggle_TRAF_GREEN2 (void) //change green for traffic light 2 to opposite state (on or off) than previous 
{
	GPIOC->ODR ^= (1<<Traf_Green2); //toggle pin9
}
void toggle_TRAF_WHITE (void) //change white for traffic light white mane to opposite state (on or off) than previous 
{
	GPIOF->ODR ^= (1<<Traf_White); //toggle pin10
}

void traf_pause (void) //puts traffic lights so that red is on for both of them (for pedestrian crossing)
{
  GPIOC_led_on_PushPull(Traf_Red1);     //turn on G traf1
  GPIOC_led_on_OpenDrain(Traf_Red2);    //turn on R traf2
	
	GPIOC_led_off_PushPull(Traf_Green1);  //turn all others off
	GPIOC_led_off_PushPull(Traf_Yellow1);
	GPIOC_led_off_OpenDrain(Traf_Green2);
	GPIOC_led_off_OpenDrain(Traf_Yellow2); 
}	







 