#include "interruption.h"
/*毫秒延时函数*/
void delay_ms(unsigned int i)
{
   unsigned int j;
   for( ;i>0;i--)
   {
      for(j=110;j>0;j--);
   }
}
/*外部中断0,中断号为0*/
void Int0Init()
{
	//设置INT0
	IT0=1;//跳变沿出发方式（下降沿）
	EX0=1;//打开INT0的中断允许。	
	EA=1;//打开总中断	
}
/*外部中断1，中断号为2*/
void Int1Init()
{
	//设置INT1
	IT1=1;//跳变沿出发方式（下降沿）
	EX1=1;//打开INT1的中断允许。	
	EA=1;//打开总中断	
}
/*定时器0，中断号为1*/
void Timer0Init()
{
	TMOD|=0X01;//选择为定时器0模式，工作方式1，仅用TR0打开启动。

	TH0=0XFC;	//给定时器赋初值，定时1ms
	TL0=0X18;	
	ET0=1;//打开定时器0中断允许
	EA=1;//打开总中断
	TR0=1;//打开定时器			
}
/*定时器1，中断号为3*/
void Timer1Init()
{
	TMOD|=0X10;//选择为定时器1模式，工作方式1，仅用TR1打开启动。

	TH1=0XFC;	//给定时器赋初值，定时1ms
	TL1=0X18;	
	ET1=1;//打开定时器1中断允许
	EA=1;//打开总中断
	TR1=1;//打开定时器			
}
/*串口通信，中断号为4*/
void UsartInit()
{
	SCON=0X50;			//设置为工作方式1
	TMOD=0X20;			//设置计数器工作方式2
	//PCON=0X80;			//波特率加倍
	TH1=0XFD;				//计数器初始值设置，注意波特率是(波特率加倍）4800的；（波特率不加倍）9600（0XFD)
	TL1=0XFD;
	//ES=1;						//打开接收中断
	EA=1;						//打开总中断
	TR1=1;					//打开计数器
}
