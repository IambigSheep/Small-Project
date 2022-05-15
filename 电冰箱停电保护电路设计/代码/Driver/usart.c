#include "usart.h"

bit busy;
void UartInit(void)		//9600bps@11.0592MHz
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR &= 0xBF;		//��ʱ��ʱ��12Tģʽ
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x20;		//���ö�ʱ��ģʽ
	TL1 = 0xFD;		//���ö�ʱ��ʼֵ
	TH1 = 0xFD;		//���ö�ʱ����ֵ
	ET1 = 0;		//��ֹ��ʱ��%d�ж�
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
//	TI = 1;				//���Ҫʹ��printf����������Ӵ˾�
}


/*----------------------------
���ʹ�������
----------------------------*/
void SendData(unsigned char dat)
{
    while (busy);               //�ȴ�ǰ������ݷ������
    ACC = dat;                  //��ȡУ��λP (PSW.0)  
    busy = 1;
    SBUF = ACC;                 //д���ݵ�UART���ݼĴ���
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
�����ַ���
----------------------------*/
void SendString(char *s)
{
    while (*s)                  //����ַ���������־
    {
        SendData(*s++);         //���͵�ǰ�ַ�
    }
}

