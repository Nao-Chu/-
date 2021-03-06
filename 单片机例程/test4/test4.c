#include<reg52.h>

#define uint 		unsigned int
#define uchar 		unsigned char
#define GPIO_DIG	P0
#define GPIO_KEY	P1

uint KEY_VALUE;
uchar unit[8]={0x07,0x0b,0x0d,0x0e,0x70,0xb0,0xd0,0xe0};
sbit led1 = P2^0;
sbit led2 = P2^1;
sbit led3 = P2^2;
sbit led4 = P2^3;
sbit led5 = P2^4;
sbit led6 = P2^5;
sbit led7 = P2^6;
sbit led8 = P2^7;
void delay(uint x)
{
	while(x--);
}

void keyDown()
{
	uint i;
	uint a=0;
	GPIO_KEY = 0x0f;
	if(GPIO_KEY != 0x0f)
	{
		delay(1000);
		if(GPIO_KEY != 0x0f){
			for(i=0;i<4;i++){
				if(GPIO_KEY == unit[i]){
					 KEY_VALUE = i;
					 break;
				}
			}

			GPIO_KEY = 0xf0;
			for(i=4;i<8;i++){
				if(GPIO_KEY == unit[i]){
					KEY_VALUE += ((i-4)*4);
					break;
				}
			}
			if( (a<500) && (GPIO_KEY != 0xf0)){
				delay(10000);
				a++;	
			}
		}
	}	
}

void main()
{
	KEY_VALUE = 16;
	while(1)
	{
		keyDown();
		switch(KEY_VALUE)
		{
		 	case 0:
				led1 = ~led1; 
				break;	 
			case 1:
				led2 = ~led2;
				break;
			case 2:
				led3 = ~led3;
				break;
			case 3: 
				led4 = ~led4;
				break;

			case 4:
				led5 = ~led5;
				break;	 
			case 5:
				led6 = ~led6;
				break;
			case 6:
				led7 = ~led7;
				break;
			case 7: 
				led8 = ~led8;
				break;

			case 8:
				led1 = ~led1;
				break;	 
			case 9:
				led2 = ~led2;
				break;
			case 10:
				led3 = ~led3;
				break;
			case 11: 
				led4 = ~led4;
				break;

			case 12:
				led5 = ~led5;
				break;	 
			case 13:
				led6 = ~led6;
				break;
			case 14:
				led7 = ~led7;
				break;
			case 15: 
				led8 = ~led8;
				break;
		}
		KEY_VALUE = 16;
	}
}