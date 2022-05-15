#ifndef __BSP_DS1302_H
#define __BSP_DS1302_H

#include "main.h"


sbit SCK=P1^0;		
sbit SDA=P1^1;		
sbit RST = P1^2;   // DS1302¸´Î»

void Set_Rtc(unsigned char* ucRtc);

void Read_Rtc(unsigned char* ucRtc);

#endif