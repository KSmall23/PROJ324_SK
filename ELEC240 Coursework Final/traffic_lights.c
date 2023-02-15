#include "traffic_lights.h"
#include "LED.h"
#include "ext_interrupts.c"



static int traffic_counter=0;  //global variable to count through traffic light sequence
static int traffic_pause=0;    //global variable used to count through white man sequence 

void traffic_light_sequence (void)  //function that goes through traffic light sequence for both traffic lights
{	
if(traffic_counter==0) //Traffic light 1: red on, Traffic light 2: green on
{
  GPIOC_led_on_PushPull(Traf_Red1);    //turn on R traf1
  GPIOC_led_on_OpenDrain(Traf_Green2); //turn on G traf2
	
	GPIOC_led_off_PushPull(Traf_Green1);  //turn all others off
	GPIOC_led_off_PushPull(Traf_Yellow1);
	GPIOC_led_off_OpenDrain(Traf_Yellow2);
	GPIOC_led_off_OpenDrain(Traf_Red2);  
}

if(traffic_counter==2) //Traffic light 1: red and yellow on, Traffic light 2: yellow on
{
  GPIOC_led_on_PushPull(Traf_Red1);     //turn on R traf1
  GPIOC_led_on_PushPull(Traf_Yellow1);  //turn on Y traf1`
	GPIOC_led_on_OpenDrain(Traf_Yellow2); //turn on Y traf2
	
	GPIOC_led_off_PushPull(Traf_Green1);  //turn all others off
	GPIOC_led_off_OpenDrain(Traf_Green2);
	GPIOC_led_off_OpenDrain(Traf_Red2);  
}

if(traffic_counter==4) //Traffic light 1: green on, Traffic light 2: red on
{
  GPIOC_led_on_PushPull(Traf_Green1);  //turn on G traf1
  GPIOC_led_on_OpenDrain(Traf_Red2);   //turn on R traf2
	
	GPIOC_led_off_PushPull(Traf_Yellow1);  //turn all others off
	GPIOC_led_off_PushPull(Traf_Red1);
	GPIOC_led_off_OpenDrain(Traf_Green2);
	GPIOC_led_off_OpenDrain(Traf_Yellow2);  
}

if(traffic_counter==6) //Traffic light 1: red and yellow on, Traffic light 2: yellow on
{
  GPIOC_led_on_PushPull(Traf_Yellow1);  //turn on Y traf1`
	GPIOC_led_on_OpenDrain(Traf_Yellow2); //turn on Y traf2
	GPIOC_led_on_OpenDrain(Traf_Red2);    //turn on R traf2
	
	GPIOC_led_off_PushPull(Traf_Green1);  //turn all others off
	GPIOC_led_off_PushPull(Traf_Red1);
	GPIOC_led_off_OpenDrain(Traf_Green2);	  
}

traffic_counter++; //each state is a multiple of 2 so change in state every two seconds

if (traffic_counter>6) //once all states have run through, reset counter
{                      //once all states have run through, reset counter
 traffic_counter=0;    //once all states have run through, reset counter    
}	                     //once all states have run through, reset counter
}


void white_man_sequence (void) //sequence for when pedestrian button is pressed
{	
if(white_man!=0) //if button has been pressed white man=1 and so enter
{
   traf_pause();    //sets lights to red
	 traffic_pause++; //increment counter
}	
//if counter is in first ten second or every other second after that upto 20 white man on
if((traffic_pause==1)| (traffic_pause==11)|(traffic_pause==13)|(traffic_pause==15)| (traffic_pause==17)|(traffic_pause==19)) 
{
  white_led_on; //white man on
}
//if counter is ater 10 seconds,every other second turn white man off to flash to show lights are about to resume
if((traffic_pause==12)|(traffic_pause==14)|(traffic_pause==16)|(traffic_pause==18))
{
  white_led_off; //white man off
}
if(traffic_pause==20) //if counter is 20 (twenty seconds have passed) turn of white man, reset counter and reset entry condition to sequence as well turning traffic light two to red and yellow
{
  white_led_off;                        //white man off
	GPIOC_led_on_OpenDrain(Traf_Yellow2); //traffic light two shows red and yellow
	traffic_pause=0;                      //resets counter 
	white_man=0;                          //resets entry condition (so function is gone back into until another pedestrian button press)
}	


}
