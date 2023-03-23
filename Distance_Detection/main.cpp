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
//DigitalIn DIP (PG_10);
//AnalogOut CarrierWave2 (DAC2_AN_PIN);

Semaphore sem(1);
Thread t1(osPriorityAboveNormal1);
EventQueue Test;

Timer Time;
float time_store;
float x=0;	

void Teest();
void QueueDispatch ();
void trh();
void StopWave_ISR();
// main() runs in its own thread in the OS
int main()
{
    StopWave.rise(StopWave_ISR);
    Red = 0;										
    CarrierWave =1;
    
    t1.start(trh);
    while (true) { 
     
     ThisThread:: sleep_for(10ms);     
     while (Bluebutton ==0);  
     ThisThread:: sleep_for(10ms);
     while (Bluebutton == 1);
     while (1) {

     Time.start();
     //for (int n = 0; n<10000; n++)
     
         CarrierWave = 0;
    
     ThisThread:: sleep_for(10ms);
     
          CarrierWave =1;
          
 
  
  
  
     ThisThread:: sleep_for(10ms);
 
    }
}
}

void Teest()
{
}

void trh()
{
    
    while (1)
    {     
        ThisThread::flags_wait_any(1);
        time_store =  Time.read_us();
        printf("time = %f\n",time_store);
        //distance = speed * time;
        //here, let speed equal approx 343m/s
        //time in us so needs to be *10^6 (e6)
        //because distance is there and back then /2
        float time_sec = time_store*0.000001;
        float distance = (343 * time_sec)/2;
        printf("distance = %f\n",distance);
        Time.stop();
        StopWave.rise(StopWave_ISR);
        Time.reset();
    } 
}



void StopWave_ISR()
{
    StopWave.rise(NULL);
    t1.flags_set(1);
}