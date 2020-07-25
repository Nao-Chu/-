#include <reg52.h>

#define uchar	unsigned char;
void UsartInit()
{
	TMOD=0x20;
	TH1=0XF9;
	TL1=0xF9;
	PCON=0x80;
	TR1=1;  
	SCON=0X50;
	ES=1;	//  串行中断允许位
	EA=1;   //  CPU中断允许位
}

void main()
{
	UsartInit();
	while(1);
}

void Usart() interrupt 4
{
	uchar receiveData;
	receiveData=SBUF;
	RI=0;
	SBUE=receiveDate;
	while(!TI);
	T1=0;
} 