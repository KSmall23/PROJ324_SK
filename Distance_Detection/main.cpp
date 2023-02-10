#include "mbed.h"
#include "uop_msb.h"
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>



//#define T 0.000024752475247524752
#define pi 3.141592653589793238462643383279

int Freq = 40400;
double Fs = 10000.0;
double T = 1.0/Fs;
uint32_t n = 0;

AnalogOut CarrierWave (DAC1_AN_PIN);


Thread t1;
EventQueue Test;

void Teest();
void QueueDispatch ();
// main() runs in its own thread in the OS
int main()
{
    //Timer tmr;
    //tmr.start();
    // t1.start(QueueDispatch);
    //  Test.call_every(0.000024752475247524752s,Teest);
     while (true) { 
    // cout<<Freq<<endl;
    // cout<<T<<endl;
     //  if (tmr.elapsed_time() >= 1ms) {
     //       tmr.reset();
         //float data =0.5f + 0.5f*5*cos(2*pi*Freq*T*n);
         CarrierWave = 0.5f + 0.5f*0.5*sin(2*pi*Freq*T*n);
         n = (n == 9999) ? 0 : (n+1);
    // }
     //  cout<<n<<endl;
 
    }
}

// void Teest()
// {
//  float data = 0.5f + 0.5f*5*cos(2*3.14*Freq*n);
//  CarrierWave = data;
//  n = (n == 999) ? 0 : (n+1);
// };

// void QueueDispatch ()
// {
//     Test.dispatch_forever();
// }

