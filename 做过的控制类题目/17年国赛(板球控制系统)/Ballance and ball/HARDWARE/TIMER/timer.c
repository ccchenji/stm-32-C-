#include "timer.h"
#include "PID.h"
#include "OLED.H"
extern short fps;
char flag=0;
short timer=0;
char flag_mode=0;
extern float err_X;
extern float err_Y;
short MODEII_timer=0;
short MODEII_flag=0;

short MODEIII_flag=0;
short MODEIII_timer=0;

short MODEVI_flag=0;
short MODEVI_timer=0;
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

/*

    1       2      3       4       5       6         7         8         9       T1        T2       T3         T4  
x   0                     93      94                                    24     131                 57         57

  
y   0                     32      103                                   176     63                 66         142

*/
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
void TIM4_IRQHandler(void)   
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) 
		{ 
			   timer++;
			   if(timer>=100)
			 {
					 flag=1; 
					 timer=0;
			 }
	  //ģʽ0
				if(flag_mode==0)
				{
				 TIM_SetCompare1(TIM3,1350);
		     TIM_SetCompare2(TIM3,1450);
				}
				
		//ģʽ1
				if(flag_mode==1)
				{
				  TIM_SetCompare1(TIM3,1350+PID_control_X(94));
		      TIM_SetCompare2(TIM3,1480+PID_control_Y(103));
				}
				
	 //ģʽ2
				if(flag_mode==2)
				{
					if(err_X<=3&&err_X>=-3&&err_Y>=-3&&err_Y<=3)
					{
			       MODEII_flag=1;
					}
					else
					{
						 MODEII_flag=0;
					}
					if(MODEII_flag==1)
					{
						  MODEII_timer++;
						 if(MODEII_timer>=10000)
						 {
							  MODEII_timer=10000;
						 }
					}
					if(MODEII_timer<=300)
					{
					  TIM_SetCompare1(TIM3,1350+PID_control_X(93));
		        TIM_SetCompare2(TIM3,1480+PID_control_Y(30));
					}
					else
					{
						 TIM_SetCompare1(TIM3,1350+PID_control_X(94));
		         TIM_SetCompare2(TIM3,1480+PID_control_Y(103));
					}
				}
				
				
	 //ģʽ3
				if(flag_mode==3)
				{
					 if(MODEIII_flag==0)
					 {
					   TIM_SetCompare1(TIM3,1350+PID_control_X(131));
		         TIM_SetCompare2(TIM3,1480+PID_control_Y(63));
					 }
					 if(MODEIII_flag==1)
					 {
								TIM_SetCompare1(TIM3,1350+PID_control_X(57));
		            TIM_SetCompare2(TIM3,1480+PID_control_Y(66));
					 }
					 if(MODEIII_flag==2)
					 {
						   TIM_SetCompare1(TIM3,1350+PID_control_X(57));
		           TIM_SetCompare2(TIM3,1480+PID_control_Y(142));
					 }
					 if(MODEIII_flag==3)
					 {
						  TIM_SetCompare1(TIM3,1350+PID_control_X(24));
		          TIM_SetCompare2(TIM3,1480+PID_control_Y(176));
           }						
					 if(err_X<=10&&err_X>=-10&&err_Y>=-10&&err_Y<=10)
					 { 	 
									  MODEIII_timer++;
									 if(MODEIII_timer>=100)
									 {
										 MODEIII_flag++;
										 if(MODEIII_flag>=3)
										 {
											  MODEIII_flag=3;
										 }
									 }
					 }
					 else
					 {
						   MODEIII_timer=0;
					 }
				}
	  //ģʽ4	
		  if(flag_mode==4)
			{
				 if(MODEVI_flag==0)
				 {
					   TIM_SetCompare1(TIM3,1350+PID_control_X(169));
		         TIM_SetCompare2(TIM3,1480+PID_control_Y(100));
				 }
				 if(MODEVI_flag==1)
				 {
					   TIM_SetCompare1(TIM3,1350+PID_control_X(96));
		         TIM_SetCompare2(TIM3,1480+PID_control_Y(177));
				 }
				 if(MODEVI_flag==2)
				 {
					   TIM_SetCompare1(TIM3,1350+PID_control_X(24));
		         TIM_SetCompare2(TIM3,1480+PID_control_Y(177));
				 }
				if(err_X<=10&&err_X>=-10&&err_Y>=-10&&err_Y<=10)
				{
					 MODEVI_timer++;
					 if(MODEVI_timer>=100)
					 {
						  MODEVI_flag++;
						 if(MODEVI_flag>=2)
						 {
							  MODEVI_flag=2;
						 }
					 }
				}
				else
				{
					 MODEVI_timer=0;
				}
			}
		    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  
		}
}











