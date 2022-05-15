/********************************************电冰箱停电保护程序**************************************************/
/*
版本：		电冰箱停电保护程序 1.0
作者：		IambigSheep
平台：		STC89C52
晶振频率：	11.0592MHZ
编写软件：	Keil 5
烧写软件：	STC-ISP
日期：		2022年5月15日
*/
//注意：本程序需烧写两次，第一次烧写时向DS1302写入你想输入的时间（解除第23行的注释），第二次烧写时注释掉第23行。
/***************************************************************************************************************/
#include "main.h"


//DS1302专用
unsigned char ucRtc[3] ={0,0,0};		//数组分别存放 时 分 秒

///用户自定义区 
sbit RELAY = P0^7;		//继电器			//1闭合 0断开
bit time_flag;			//时间标志位
void main()
{
	Set_Rtc(ucRtc);		//向DS1302写入时间		第一次烧写时使用
	UartInit();			//串口初始化
	
	while(1)
	{
		Read_Rtc(ucRtc);		//读取时间		第一次烧写程序时添加
//		测试用		
		if((ucRtc[0] == 0) && (ucRtc[1] == 0)) time_flag = 1;		//0点0分继电器闭合
		if((ucRtc[0] == 0) && (ucRtc[1] == 1))	time_flag =0;		//0点3分继电器断开
		if((ucRtc[0] == 0) && (ucRtc[1] == 2)) time_flag =1;		//12点0分继电器闭合
		if((ucRtc[0] == 0) && (ucRtc[1] == 3))	time_flag =0;		//12点3分继电器断开
		
////		实际使用		
//		if((ucRtc[0] == 0) && (ucRtc[1] == 0)) time_flag = 1;		//0点0分继电器闭合
//		if((ucRtc[0] == 0) && (ucRtc[1] == 3))	time_flag =0;		//0点3分继电器断开
//		if((ucRtc[0] == 12) && (ucRtc[1] == 0)) time_flag =1;		//12点0分继电器闭合
//		if((ucRtc[0] == 12) && (ucRtc[1] == 3)) time_flag =0;		//12点3分继电器断开
		
		if(time_flag) RELAY = 1;		//继电器闭合
		else if(!time_flag) RELAY = 0;		//继电器断开
		
//      串口调试使用
		SendData(ucRtc[0]);			
		SendData(ucRtc[1]);
		SendData(ucRtc[2]);
		Delay1ms(1000);
	}
}