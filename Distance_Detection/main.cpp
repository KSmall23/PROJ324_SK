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
InterruptIn StopWave (BNC_AN_PIN);
DigitalOut Red (TRAF_RED1_PIN);
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
     while (Bluebutton ==0);  // std::chrono::duration(1us);
     ThisThread:: sleep_for(10ms);
     while (Bluebutton == 1);
     ThisThread:: sleep_for(10ms);
     Time.start();
     for (int n = 0; n<100000; n++)
     {
         CarrierWave = 0;
     }
    // printf("stopWave = %f", x);
    //  for (int n = 0; n<1000000; n++)
    //  {
          CarrierWave =0.33;
    //  } 
  
  
  
   // ThisThread:: sleep_for(osWaitForever);
//    CarrierWave = 0.5f + 0.5f*0.5*sin(2*pi*Freq*T*n);
//          n = (n == 999999) ? 0 : (n+1);
 
    }
}

void Teest()
{
          //  uint16_t cw = 0;//+ (4095*0.5*sin(2*pi*Freq*T*n));
           //          n = (n == 100) ? 0 : (n+1);
        // DAC->DHR12R2 = cw;
        // DAC->DHR12R1 = cw;
   // sem.release();
// t1.flags_set(1);
}

void trh()
{
    
    while (1)
    {     
        ThisThread::flags_wait_any(1);
        printf("Wave = %f",x);
        Red = !Red;
        time_store =  Time.read_us();
        printf("time = %f",time_store);
        Time.stop();
        Time.reset();
        ThisThread:: sleep_for(50ms);
        ThisThread::flags_clear(1);
      

    } 
}


//     sem.acquire();
    //  ThisThread ::flags_wait_any(1);
  //      uint32_t cw = 2048;//+ (4095*0.5*sin(2*pi*Freq*T*n));
    //    DAC1->DHR12R1 = cw;
       //  CarrierWave = 0.5f + 0.5f*0.5*sin(2*pi*Freq*T*n);
      //   n = (n == 100) ? 0 : (n+1);
void StopWave_ISR()
{
    StopWave.rise(NULL);
   //x = StopWave;
  // if ( x>=1)
   {
       t1.flags_set(1);
      //osSignalSet(t1.get_id(), 1); 
   }
}