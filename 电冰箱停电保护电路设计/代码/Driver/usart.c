#include "usart.h"

bit busy;
void UartInit(void)		//9600bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR &= 0xBF;		//定时器时钟12T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFD;		//设置定时初始值
	TH1 = 0xFD;		//设置定时重载值
	ET1 = 0;		//禁止定时器%d中断
	TR1 = 1;		//定时器1开始计时
//	TI = 1;				//如果要使用printf函数必须添加此句
}


/*----------------------------
发送串口数据
----------------------------*/
void SendData(unsigned char dat)
{
    while (busy);               //等待前面的数据发送完成
    ACC = dat;                  //获取校验位P (PSW.0)  
    busy = 1;
    SBUF = ACC;                 //写数据到UART数据寄存器
   while(!TI);
	TI=0;
	   busy = 0;
}
//void  SendData(unsigned char dat)
//{
//    SBUF=dat;  
//	while(!TI);TI=0;	  
//}
/*----------------------------
发送字符串
----------------------------*/
void SendString(char *s)
{
    while (*s)                  //检测字符串结束标志
    {
        SendData(*s++);         //发送当前字符
    }
}

