#ifndef _TRAFFIC_LIGHTS_H_
#define _TRAFFIC_LIGHTS_H_
#include <stm32f4xx.h>

void traffic_light_sequence (void);  //standard traffic light sequence; to be used in 1 second timer
void white_man_sequence (void);      //sequence which happens when blue button is pressed to simulate pedestrian crossing; to be used in 1 second timer


#endif