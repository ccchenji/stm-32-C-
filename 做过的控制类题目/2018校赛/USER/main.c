/*************************************************************************************************
PWM输出:PA^7
ADC采集:PA^1
OLED引脚:CS:PA^4   DC:PB^1   RES:PB^0    DIN:PA^0     CLK:PA^5
驱动电路:IN1:PA^8   IN2:PB^5
按键：KEY_UP:PA^2    KEY_DOWN:PA^3    kEY_LEFT:PB^3     KEY_RIGHT:PB^4      kEY_OK:PB^8    kEY_BANK:PB^9
正交解码：PB^6   PB^7
**************************************************************************************************/
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "menu.h"
#include "pwm.h"
#include "adc.h"
#include "timer.h"
#include "IN.H"
#include "stmflash.h"
#include "PID.H"
extern MenuPage fatherPage;
extern MyPID nowPID;
float Mydata = 0;
short PidData[6] = { 0 };
void usart2_send_char(u8 c)
{
	while((USART2->SR&0X40)==0); 
	USART2->DR=c;   	
} 
void usart1_send_char(u8 c)
{
	while((USART1->SR&0X40)==0); 
	USART1->DR=c;   	
} 
//读出flash里面的数据
union SolveData
{
	float f;
	short data[2];
}Solve;
float SolveMyData(union SolveData Mydata, short data1, short data2)
{
	Mydata.data[0] = data1;
	Mydata.data[1] = data2;
	return Mydata.f;
}
int main(void)
{
	u8 len=0;
	u8 t=0;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 //串口初始化为9600
	//KEY_Init();
	//Init_Menue(&fatherPage);//菜单初始化
	//TIM2_Int_Init(9, 7199);//定时器初始化时间为10ms
	//Encoder_Init_TIM4();
	//TIM3_PWM_Init(899, 7);//PWM初始化频率为10K
	//Adc_Init();//ADC初始化
	//IN_Init();//电机驱动初始化
//	STMFLASH_Read(0X0801FC00, (u16 *)PidData, sizeof(PidData));
//	nowPID.Kp = SolveMyData(Solve, PidData[0], PidData[1]);
//	nowPID.Kd = SolveMyData(Solve, PidData[2], PidData[3]);
//	nowPID.Ki = SolveMyData(Solve, PidData[4], PidData[5]);
	while (1)
	{
//		Menue_Show();
//		KeyNumGet(KEY_Scan());
//		Mydata = Get_Adc(1);
		if(USART2_RX_STA&0x8000)
		{					   
			len=USART2_RX_STA&0x3fff;//得到此次接收到的数据长度
			for(t=0;t<len;t++)
			{
				USART2->DR=USART2_RX_BUF[t];
				while((USART2->SR&0X40)==0);//等待发送结束
			}
			USART2_RX_STA=0;
		}
		//usart2_send_char(44);
		//usart1_send_char(65);
	}
}
