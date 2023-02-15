#ifndef _USART_H_
#define _USART_H_
#include <stm32f429xx.h>
#include <stdio.h>

#define USART_MODULE	USART3
#define USART_PORT		GPIOD
#define USART_TX_pin	8
#define USART_RX_pin	9
#define BAUDRATE			9600
#define USART_RXNE_pin 5
#define USART_RXNEIE_pin 5
#define USART3_INTERRUPT 39

FILE __stdout; // used for output – printf()
FILE __stdin; // used for input – getchar()


int fputc(int ch, FILE *f);             //allows printf to print string to USART and LCD
int fgetc(FILE *f);                     //allows getchar to get data from USART
int USART3_GetData(void);               //gets data from USART

void send_usart(unsigned char d);       //sends one character to USART
void init_USART(void);                  //configs USART
void send_usart_string(const char *d);  //send string to USART
void USART_Interrupt_Enable(void);      //enables USART3 interrupt
void USART3_IRQHandler (void);          //USART3 INTERRUPT SERVICE ROUTINE happens whenever anything is typed in USART terminal

#endif
