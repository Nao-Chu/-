### 第六课 ADC

```c
#include<reg52.h>
#include<intrins.h>

#define 	u8		unsigned char
#define 	u16		unsigned int

sbit DOUT = P3^7;	//输出
sbit CLK  = P3^6;	//时钟
sbit DIN  = P3^4;	//输入
sbit CS   = P3^5;   //片选

sbit LSA = P2^2;
sbit LSB = P2^3;
sbit LSC = P2^4;

u8 disp[4];
u8 code smgduan[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void delay(u8 x)
{
	while(x--);
}

void SPI_Write(u8 dat)
{
	u8 i;
	CLK = 0;
	for(i = 0; i < 8; i++)
	{
		DIN = dat >> 7;
		dat <<= 1;
		CLK = 0;
		CLK = 1;
	}
}

u16 SPI_Read()
{
	u16 i,dat=0;
	CLK=0;
	for(i = 0; i < 12; i++)
	{
		dat <<= 1;
		CLK = 1;
		CLK = 0;
		dat |= DOUT;
	}
	return dat;
}

u16 Read_AD_Data(u8 cmd)
{
	u8 i;
	u16 AD_Value;
	CLK = 0;
	CS  = 0;
	SPI_Write(cmd);
	for(i = 6;i > 0; i--);
	CLK = 1;
	_nop_();
	_nop_();
	CLK = 0;
	_nop_();
	_nop_();
	AD_Value=SPI_Read();
	CS  = 1;
	return AD_Value;
}

void datapros()
{
	u16 temp;
	static u8 i;
	if(i == 50)
	{
		i = 0;
		temp = Read_AD_Data(0xa4);
	}
	i++;
	disp[0] = smgduan[temp/1000];
	disp[1] = smgduan[temp%1000/100];
	disp[2] = smgduan[temp%1000%100/10];
	disp[3] = smgduan[temp%1000%100%10/1];
}

void DigDisplay()
{
	u8 i;
	for(i = 0; i < 4; i++)
	{
		switch(i)
		{
			case(0):
				LSA=0;LSB=0;LSC=0;break;
			case(1):
				LSA=1;LSB=0;LSC=0;break;
			case(2):
				LSA=0;LSB=1;LSC=0;break;
			case(3):
				LSA=1;LSB=1;LSC=0;break;
		}
		P0=disp[3-i];
		delay(100);
		P0 = 0x00;	   // 消影
	}
}

void main()
{
	while(1)
	{
		datapros();
		DigDisplay();
	}
}
```

