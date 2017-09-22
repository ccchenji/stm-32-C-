#include "timer.h"
#include "control.h"
#include "math.h"
#include "key.h"
#include "inv_mpu.h"
#include "math.h"
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
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
int flag=1;
double t=0;
int Angle=0;
double Set_Angley=30;
double Set_Anglex=35;
float rangeII=35.0;//ģʽII�ķ�ֵ
double rangeIIIx=20.0;
double rangeIIIy=20.0;
float pitch=0;
float roll=0;
float yaw;
float long_roll=0;
float long_pitch=0;
int i=0;
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
		TIM4, //TIM2
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
void TIM4_IRQHandler(void)   //TIM4�ж�
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
 /****************ģʽIok********************/  
			mpu_dmp_get_data(&pitch,&roll,&yaw);
			long_roll=tan((roll)*3.14/180)*98.5;	
			long_pitch=tan((pitch+3)*3.14/180)*80;
			if(flag==0)
		{
			 PID_change1(240,6300,0);//1100��1400000��5   260   6300
	   	 PID_change2(260,6000,0);//2100��1400000��5
			 t=t+0.008;
			 Set_Angley=50*sin(2*3.14*t/1.8);	
			if(Set_Angley<=0)
			{
		   TIM_SetCompare2(TIM3,(int)(PID_Control(Set_Angley)));
			 TIM_SetCompare3(TIM2,0);
			}
			else
			{
		   TIM_SetCompare3(TIM2,(int)(PID_Contro2(Set_Angley)));
		   TIM_SetCompare2(TIM3,0);
			}
		}
 /****************ģʽIIok**********************/
				if(flag==1)
		{
			 PID_change1(60,100,0);//1100��1400000��5   240   6300
	   	 PID_change2(60,100,0);//2100��1400000��5   260   6000
			 
			if(rangeII>40&&rangeII<=50)
			 {
				  PID_change1(200,630,0);//1100��1400000��5   260   6300
	   	    PID_change2(200,600,0);//2100��1400000��5
			 }
			 if(rangeII>50)
			 {
				  PID_change1(180,630,0);//1100��1400000��5   260   6300
	   	    PID_change2(180,600,0);//2100��1400000��5
			 }
			 t=t+0.008;
			 Set_Angley=-20                   ;//rangeII*sin(2*3.14*t/1.8);	
			if(Set_Angley<=0)
			{
		   TIM_SetCompare2(TIM3,(int)(PID_Control(Set_Angley)));
			 TIM_SetCompare3(TIM2,0);
			}
			else
			{
		   TIM_SetCompare3(TIM2,(int)(PID_Contro2(Set_Angley)));
		   TIM_SetCompare2(TIM3,0);
			}
		}
 /******************ģʽIII*********************/
		if(flag==2)
		{			  
			 PID_change1(1100,1400000,5);//1100��1400000��5   260   6300
	   	 PID_change2(2100,1400000,5);//2100��1400000��5
       if((-30-long_roll)<2&&(-30-long_roll)>-2)
			 {
				   		 Set_Angley=30;		
			 }	
       if((30-long_roll)<2&&(30-long_roll)>-2)
			 {
				   		 Set_Angley=-30;		
			 }				 
			 	if(Set_Angley<=0)
			{
		   TIM_SetCompare2(TIM3,(int)(PID_Control(Set_Angley)));
			 TIM_SetCompare3(TIM2,0);
			}
			else
			{
		   TIM_SetCompare3(TIM2,(int)(PID_Contro2(Set_Angley)));
		   TIM_SetCompare2(TIM3,0);
			}
		}
/*******************ģʽIVok************************/
if(flag==3)
{
	    PID_change1(0,13000,0);
	    PID_change2(0,13000,0);
	    PID_change3(0,13000,0);
	    PID_change4(0,13000,0);
	 		if(roll<0)
			{
		   TIM_SetCompare2(TIM3,(int)(PID_Control(0)));
			 TIM_SetCompare3(TIM2,0);
			}
			if(roll>=0)
			{
		   TIM_SetCompare3(TIM2,(int)(PID_Contro2(0)));
		   TIM_SetCompare2(TIM3,0);
			}
			 if(pitch<0)
			 {
				 TIM_SetCompare2(TIM2,0);
			   TIM_SetCompare1(TIM3,(int)(PID_Contro4(0)));
				  
			 }
		  if(pitch>0)
			 {
			    TIM_SetCompare2(TIM2,(int)(PID_Contro3(0)));
			    TIM_SetCompare1(TIM3,0);
			 }
}
/*******************ģʽV***********************/
		  if(flag==4)
		  {
				t=t+0.008;//0.032
        Set_Angley=atan((25*cos(2*3.14*t/1.8))/87)*180/3.14;	
        Set_Anglex=atan((25*sin(2*3.14*t/1.8))/87)*180/3.14;			
//			if(Set_Angley<=0)
//			{
//		   TIM_SetCompare2(TIM3,(int)(PID_Control(Set_Angley)));
//			 TIM_SetCompare3(TIM2,0);
//			}
//			else
//			{
//		   TIM_SetCompare3(TIM2,(int)(PID_Contro2(Set_Angley)));
//		   TIM_SetCompare2(TIM3,0);
//			}
			 if(Set_Anglex<=0)
			 {
				 TIM_SetCompare2(TIM2,0);
			   TIM_SetCompare1(TIM3,(int)(PID_Contro4(Set_Anglex)));
				  
			 }
			 else
			 {
			    TIM_SetCompare2(TIM2,(int)(PID_Contro3(Set_Anglex)));
			    TIM_SetCompare1(TIM3,0);
			 }
		 }
			
	  }
		    TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
}










