#include "mbed.h"
#include "uop_msb.h"
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>



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
    CarrierWave =0.33;
    
     
//    // t1.set_priority(osPriorityRealtime);
    t1.start(trh);
//    Tick.attach_us(Teest,12);
     while (true) { 
    ThisThread:: sleep_for(10ms);     
     while (Bluebutton ==0);  // std::chrono::duration(1us);
     ThisThread:: sleep_for(10ms);
     while (Bluebutton == 1);
     
     Time.start();
     for (int n = 0; n<100000; n++)
     {
         CarrierWave = 0;
        // if (DIP> 0) {
       //   Green = !Green;
       //  }
     }
    // printf("stopWave = %f", x);
    //  for (int n = 0; n<1000000; n++)
    //  {
          CarrierWave =0.33;
          StopWave.rise(StopWave_ISR);
    //  } 
  
  
  
   // ThisThread:: sleep_for(osWaitForever);
//    CarrierWave = 0.5f + 0.5f*0.5*sin(2*pi*Freq*T*n);
//          n = (n == 999999) ? 0 : (n+1);
 
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
        //printf("Wave = %f",x);
        //Red = !Red;
        time_store =  Time.read_us();
        printf("time = %f\n",time_store);
        Time.stop();
        Time.reset();
        //ThisThread:: sleep_for(50ms);
        
        //ThisThread::flags_clear(1);
      

    } 
}



void StopWave_ISR()
{
    StopWave.rise(NULL);
   // Green = !Green;
    t1.flags_set(1);
}