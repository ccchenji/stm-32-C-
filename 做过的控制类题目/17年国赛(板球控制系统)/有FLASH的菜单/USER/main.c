#include "sys.h"
#include "OLED.H"
#include "delay.h"
#include "usart.h"
#include "pwm.h"
#include "timer.h"
#include "menu.h"
void send_date(unsigned short date );
short Recive_Date(void);
short receive_date[2];
short fps=0;

extern float err_X;
extern float pid_x_lasterror_save[10];
int main(void)
{		
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为9600
	TIM3_PWM_Init(19999,71);   
	TIM4_Int_Init(99,7199);
  KEY_Init();
	OLED_Init();
	while(1)
	{
		Recive_Date();
    Menu_Init();	
	}
	
 }
 
 
 void send_date(unsigned short date )
{
	   u8 tbuf[6];
     u8 i=0;	 
	  union B_F
    {
	    char Byte[2];
	    unsigned short f;
    } fl;  
    fl.f=date;
		tbuf[0]='A';
		tbuf[1]='B';
		tbuf[2]=fl.Byte[0];
		tbuf[3]=fl.Byte[1];
		tbuf[4]='\r';
		tbuf[5]='\n';
		for(i=0;i<6;i++)
		{
			  USART1->DR=tbuf[i];
				while((USART1->SR&0X40)==0);//等待发送结束
		}
 }

short Recive_Date()
{
	if(USART_RX_STA&0x8000)
		{					
		  receive_date[0]=USART_RX_BUF[0]|(USART_RX_BUF[1]<<8);
			receive_date[1]=USART_RX_BUF[2]|(USART_RX_BUF[3]<<8);
			USART_RX_STA=0;
      fps++;			
		} 	
return 0;		
}
 
