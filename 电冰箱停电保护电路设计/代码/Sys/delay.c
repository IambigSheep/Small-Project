#include "delay.h"

void Delay1ms(unsigned int num)		//@11.0592MHz
{
	unsigned char i, j;
	for(;num>0;num--)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}
