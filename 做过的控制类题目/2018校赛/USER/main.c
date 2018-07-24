/*************************************************************************************************
PWM���:PA^7
ADC�ɼ�:PA^1
OLED����:CS:PA^4   DC:PB^1   RES:PB^0    DIN:PA^0     CLK:PA^5
������·:IN1:PA^8   IN2:PB^5
������KEY_UP:PA^2    KEY_DOWN:PA^3    kEY_LEFT:PB^3     KEY_RIGHT:PB^4      kEY_OK:PB^8    kEY_BANK:PB^9
�������룺PB^6   PB^7
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
//����flash���������
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
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
	//KEY_Init();
	//Init_Menue(&fatherPage);//�˵���ʼ��
	//TIM2_Int_Init(9, 7199);//��ʱ����ʼ��ʱ��Ϊ10ms
	//Encoder_Init_TIM4();
	//TIM3_PWM_Init(899, 7);//PWM��ʼ��Ƶ��Ϊ10K
	//Adc_Init();//ADC��ʼ��
	//IN_Init();//���������ʼ��
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
			len=USART2_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			for(t=0;t<len;t++)
			{
				USART2->DR=USART2_RX_BUF[t];
				while((USART2->SR&0X40)==0);//�ȴ����ͽ���
			}
			USART2_RX_STA=0;
		}
		//usart2_send_char(44);
		//usart1_send_char(65);
	}
}
