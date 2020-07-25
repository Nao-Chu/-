#include <reg52.h>

#define uint unsigned int
#define uchar unsigned char

sbit weA = P2^2;
sbit weB = P2^3;
sbit weC = P2^4;

void delay(uint x);
uchar dula[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
uchar wela[8][3] = {{1,1,1},{0,1,1},{1,0,1},{0,0,1},{1,1,0},{0,1,0},{1,0,0},{0,0,0}};
uint time;
uchar duNum;
uchar weNum;

void main()
{
	TMOD = 0X01;
	TH0 = (65536-50000)/256;
	TL0 = (65536-50000)%256;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
	time = 0;
	duNum = 0;
	weNum = 0;
	weA = wela[0][0];
	weB = wela[0][1];
	weC = wela[0][2];
	P0  = dula[0];
	while(1)
	{
		if(time >= 20)
		{
			time=0;
			duNum++;
			weNum++;
			if(duNum >= 16){
				P0=0x00;
				duNum=0;
			} 
			if(weNum >=8){
				weNum = 0;
			}
			weA = wela[weNum][0];
			weB = wela[weNum][1];
			weC = wela[weNum][2];
			P0  = dula[duNum];
		}
	}
}

void delay(uint x)
{
	for(x;x>0;x--);
}

void exter0() interrupt 1
{
	time++;
    TH0 = (65536-50000)/256;
    TL0 = (65536-50000)%256;
}