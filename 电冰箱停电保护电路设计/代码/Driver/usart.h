#ifndef _USART_H
#define _USART_H


#include "main.h"
void UartInit(void);
void SendData(unsigned char dat);
void SendString(char *s);


#endif