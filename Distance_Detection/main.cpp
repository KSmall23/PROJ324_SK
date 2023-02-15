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

//AnalogOut CarrierWave (DAC1_AN_PIN);
//AnalogOut CarrierWave2 (DAC2_AN_PIN);

Semaphore sem(1);
Thread t1(osPriorityAboveNormal1);
EventQueue Test;

void Teest();
void QueueDispatch ();
void trh();
// main() runs in its own thread in the OS
int main()
{
    	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;			//DAC port clock enable
	GPIOA->MODER|=(3u<<(2*4));			//DAC output pin set as anaglogue
    	GPIOA->MODER|=(3u<<(2*5));			//DAC output pin set as anaglogue
	
	RCC->APB1ENR|=RCC_APB1ENR_DACEN;				//DAC clock enable
	DAC->CR|=DAC_CR_EN2;										//DAC 2 enabled

	DAC->CR|=DAC_CR_EN1;										//DAC 2 enabled

    Ticker Tick;
   // t1.set_priority(osPriorityRealtime);
   // t1.start(trh);
   Tick.attach_us(Teest,12);
     while (true) { 
       // std::chrono::duration(1us);
       
    ThisThread:: sleep_for(osWaitForever);
//    CarrierWave = 0.5f + 0.5f*0.5*sin(2*pi*Freq*T*n);
//          n = (n == 999999) ? 0 : (n+1);
 
    }
}

void Teest()
{
            uint16_t cw = 0;//+ (4095*0.5*sin(2*pi*Freq*T*n));
                     n = (n == 100) ? 0 : (n+1);
        DAC->DHR12R2 = cw;
        DAC->DHR12R1 = cw;
   // sem.release();
// t1.flags_set(1);
}

void trh()
{
    while (1)
    {
   //     sem.acquire();
    //  ThisThread ::flags_wait_any(1);
  //      uint32_t cw = 2048;//+ (4095*0.5*sin(2*pi*Freq*T*n));
    //    DAC1->DHR12R1 = cw;
       //  CarrierWave = 0.5f + 0.5f*0.5*sin(2*pi*Freq*T*n);
         n = (n == 100) ? 0 : (n+1);


    } 
}