#include <reg52.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char

sbit SER = P3^4;
sbit WRCLK = P3^5;
sbit SRCLK = P3^6;


void delay(uint i)
{
	while(i--);
}

void niu();
void bi();

void SendByte(uchar date)
{
	uchar a;
	WRCLK = 1;
	SRCLK = 1;

	for(a=0;a<8;a++)
	{
		SER = date>>7;
		date<<=1;

		SRCLK=0;
		delay(10);
		SRCLK=1;
	}

	WRCLK=0;
	delay(10);
	WRCLK=1;
}

void main()
{
	while(1)
	{
		  niu();
		  bi();
	}
}	 

void niu()
{
		uint i = 10*10;
		while(i){
			SendByte(0x80);
			P0=0Xf7;
			SendByte(0x40);
			P0=0Xd7;
			SendByte(0x20);
			P0=0Xc3;
			SendByte(0x10);
			P0=0Xb7;
			SendByte(0x08);
			P0=0Xc1;
			SendByte(0x04);
			P0=0Xf7;
			SendByte(0x02);
			P0=0Xf7;
			SendByte(0x01);
			P0=0Xf7;
			i--;
		}
}
void bi()
{
		uint i = 10*10;
		while(i){
			SendByte(0x80);
			P0=0Xc7;
			SendByte(0x40);
			P0=0Xdb;
			SendByte(0x20);
			P0=0Xdb;
			SendByte(0x10);
			P0=0Xc7;
			SendByte(0x08);
			P0=0Xc7;
			SendByte(0x04);
			P0=0Xdb;
			SendByte(0x02);
			P0=0Xdb;
			SendByte(0x01);
			P0=0Xc7;
			i--;
		}
}