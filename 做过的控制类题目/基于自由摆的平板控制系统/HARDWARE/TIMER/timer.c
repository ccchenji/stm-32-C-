#include "timer.h"
#include "driver.h"
#include "ADC_filter.h"
#include "math.h"
#include "sys.h"
#include "Balance.h"
#include "filter.h"
#include "mpu6050.h"
extern float My_Angle;
float L=93;
float X=150;
float aerfa=0;
float shedingjiao=0;
float shedingjiao_save = 0;
float shedingjiao_save1=0;
float My_Angle_save = 0;
short flag=0;
float Err_My_angle=0;
short flag_way=0;
short timer_Err_My_angle=0;
float sum_Err_My_angle=0;
float Real_sum_Err_My_angle=0;
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//ͨ�ö�ʱ�� ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/12/03
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
 

//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM4_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM4, //TIM4
		TIM_IT_Update ,
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx����
							 
}
void TIM4_IRQHandler(void)  
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) 
		{
//ģʽI��
       if(flag==1)
			 {
			  Locate_Rle(5,2000,CCW);
			 }
			 	My_Angle=0.083701*MyADC_filter()-188.02;
// ���Ӳ���
			  Get_Angle();
			  My_Angle=0.083701*MyADC_filter()-188.02;
			 	aerfa=(atan((L-L*cos(My_Angle*PI/180))/(X-L*sin(My_Angle*PI/180))))*180/PI;		
			  Err_My_angle=My_Angle-My_Angle_save;
			  My_Angle_save = My_Angle;
			  if(timer_Err_My_angle<7)
				{
					 sum_Err_My_angle+=Err_My_angle;
				}
				timer_Err_My_angle++;
				if(timer_Err_My_angle>=15)
				{
					 timer_Err_My_angle=0;
					 Real_sum_Err_My_angle=sum_Err_My_angle;
					 sum_Err_My_angle=0;
				}
		    TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  
		}
}








