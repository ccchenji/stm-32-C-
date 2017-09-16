#include "reg51.h"
#include "print.h"
#include "PWM_12.h"
#include "interruption.h"
sbit AA = P3^2;
sbit BB = P3^3;
sbit OUT1 = P1^1;
sbit OUT2 = P1^2;
int num=0;
int Set_num=500;
unsigned int flag=0;
float err=0,err_last=0;
float Kp=2;
float Ki=0;
float Kd=0;
float PID_out=0;
float PIDI=0;
unsigned char PWM=0;
unsigned char AA_flag=0;
unsigned char BB_flag=0;
float PID(int num)
{
    err=Set_num-num;
	PID_out=Kp*err+Kd*(err-err_last)+Ki*PIDI;  
	if(err<=1&&err>=-1)
	{
	   PID_out=0;
    }
	 err_last=err;
	 PIDI+=err;
	 if(PID_out>0)
	 {
	    flag=0;
	 }
	 if(PID_out<0)
	 {
	    flag=1;
	    PID_out=-PID_out;
	 }
	 if(flag==0)
	 {
	    OUT1=1;
		OUT2=0;
	 }
	 if(flag==1)
	 {
	   	OUT1=0;
		OUT2=1;
     }
	 if(PID_out>=100)PID_out=100;
	 if(PID_out<=0)PID_out=0;
	return PID_out;
}	
int main()
{
  Int0Init();
  Int1Init();
  PWM_port();
  UsartInit();
  Timer0Init();
  while(1)
  {
     printf("%f\r\n",err);
	 printf("%f\r\n",err_last);
	 printf("%f\r\n",PID_out);
	 printf("%d\r\n",flag);
	 delay_ms(1000);
  }
}
void timer0 () interrupt 1
{
    TH0=(65535-10000)/256;	//给定时器赋初值，定时1ms
	TL0=(65535-10000)%256;	
    PWM=(int)(PID(num));
	PWM_change(PWM);

}
void exti0 () interrupt  0
{
   EX0=0;
	if(AA_flag==0)
	{
		if(BB==0)
			num++;
		else num--;
		AA_flag=1;BB_flag=0;
		
	}
	EX0=1;
}
void exti1 () interrupt 2
{
   EX1=0;
	if(BB_flag==0)
	{
		AA_flag=0;BB_flag=1;
	}
	EX1=1;
}









