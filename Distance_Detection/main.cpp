#include "mbed.h"
#include "uop_msb.h"
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>
#include "math.h"



//#define T 0.000024752475247524752
#define pi 3.141592653589793238462643383279

int Freq = 40000;
double Fs = 80000.0;
double T = 1.0/Fs;
uint32_t n = 0;

DigitalIn Bluebutton (USER_BUTTON);
AnalogOut CarrierWave (DAC1_AN_PIN);
InterruptIn StopWave (PG_10);
DigitalOut Red (TRAF_RED1_PIN);
DigitalOut Green (TRAF_GRN1_PIN);
uop_msb::LCD_16X2_DISPLAY LCD;
uop_msb::EnvSensor TempSens;

Thread t1(osPriorityAboveNormal1);

EventQueue Test;


Timer Time;
float time_store = 0;
float time_avg =0;
float time_store_array[100];
float x=0;	

int Temp;

void Teest();
void t2main ();
void measure();
void StopWave_ISR();

// main() runs in its own thread in the OS
int main()
{
    //sets up interrupt on received signal
    StopWave.rise(StopWave_ISR);	
    //carrier wave begins high (strangles carrrier wave)									
    CarrierWave =1;
    //start high priority measurement thread
    t1.start(measure);

    while (true)
     {  
       //wait for blue button to be pressed before anything happens     
       while (Bluebutton ==0); 
       //wait fro debounce 
       ThisThread:: sleep_for(10ms);
       while (Bluebutton == 1);

       //in a while loop so that pulses are sent conitnuously
       while (1)
        {
         //reactivate interrupt
         StopWave.rise(StopWave_ISR);
         //start timer for distance measurement   
         Time.start(); 
         //pulse goes low to allow carrier wave through    
         CarrierWave = 0;   
         //keeps pulse low for 10ms
         ThisThread:: sleep_for(10ms); 
         //pulse returns to high so carrier wave stops gettting through    
         CarrierWave =1; 
         // keeps pulse high for 10ms
         ThisThread:: sleep_for(10ms);
          
        }
     }
}

void measure()
{
    
    while (1)
    {   
        //wait for recitfied received signal or'stopwave'    
        ThisThread::flags_wait_any(1);
        //read the timer
        time_store =  Time.read_us();
        //collect 100 samples
        for (int n=100; n>0; n--)
         {
          time_store_array[n] = time_store_array[n-1];
         }
        time_store_array[0] = time_store;
        //take the mean of the samples
        for (int n=0; n<100;n++)
         {
          time_avg= time_avg+ time_store_array[n];
         }
        time_avg = time_avg/100;
        time_store = time_store;

        //correct error
        if(time_avg <1200)
        {
            time_avg =time_avg - 250;
        }
        else if ((time_avg >1200) && (time_avg <2000))
        {
            time_avg =time_avg - 300;
        }
        else if ((time_avg >2000) && (time_avg <3500))
        {
            time_avg =time_avg - 350;
        }
        else if (time_avg >3500)
        {
            time_avg =time_avg - 400;
        }
        //print time signal took from transmitter to receiver
        printf("time = %f\n",time_avg);
        //convert time from us to s
        float time_sec = time_avg*0.000001;

        Temp = TempSens.getTemperature();
         printf("temp = %d\n",Temp);
        float division_a = (Temp*1000000)/273;
        float division_b = 1 + (division_a*0.000001);
        float speed = 331*sqrtf(division_b);
        printf("speed = %f\n",speed);
        //CALCULTATE DISTANCE
        //distance = speed * time;
        //here, let speed equal approx 343m/s
        //because distance is there and back then /2   
        float distance = (speed * time_sec)/2;
        //print distance from object
        printf("distance = %f\n",distance);
        int distance_cm = (distance*100) +0.5;
        printf("distance = %d\n",distance_cm);
        LCD.locate(0,0);
        LCD.printf("distance = %d cm\n",distance_cm);
        //stop timer
        Time.stop();
       
        //reset timer to zero
        Time.reset();
    } 
}


void StopWave_ISR()
{
    StopWave.rise(NULL);
    t1.flags_set(1);
}





// void t2main ()
// {
//  while (1) {
//      ThisThread::flags_wait_any(2);
     
//       CarrierWave = ARRAY[n];
//       n++;
//       if(n==799)
//        {
           
//          n=0;
//        } 
//  }

// }
// void Teest()
// {
//     tick.detach();
//  t2.flags_set(2); 
// }

// int ARRAY[880] ={1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
// 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
// 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
// 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
// 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
// 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
// 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
// 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
// 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
// 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
