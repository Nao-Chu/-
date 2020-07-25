#include<reg52.h>

#define		uchar		unsigned char
#define		uint		unsigned int

sbit PWM = P2^1;
bit	 DIR;

uint count,value,time1;

void Timer1Init()
{
	TMOD = 0X10;
	TH0 = (65536-50000)/256;
	TL0 = (65536-50000)%256;
	EA  = 1;	  //总中断
	ET1 = 1;	  //定时器中断允许
	TR1 = 1;	  //定时器
	time1 = 0;
}

void main()
{
	Timer1Init();
	while(1)
	{
		if(count > 5)
		{
			count = 0;
			if(DIR == 1){
				value++;
			}
			if(DIR == 0){
				value--;
			}
		}

		if(value == 200){
			DIR = 0;
		}
		if(value == 0){
			DIR = 1;
		}

		if(time1>200){
			time1=0;
		}

		if(time1<value){
			PWM = 1;
		} else{
			PWM = 0;
		}
	}		
}

void exter1() interrupt 3
{
	time1++;
	count++;
	TH0 = (65536-50000)/256;
	TL0 = (65536-50000)%256;
}