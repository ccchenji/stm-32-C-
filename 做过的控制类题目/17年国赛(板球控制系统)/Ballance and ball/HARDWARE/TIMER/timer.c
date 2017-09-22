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
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//通用定时器 驱动代码			   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/12/03
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
 

//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!

/*

    1       2      3       4       5       6         7         8         9       T1        T2       T3         T4  
x   0                     93      94                                    24     131                 57         57

  
y   0                     32      103                                   176     63                 66         142

*/
void TIM4_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(  //使能或者失能指定的TIM中断
		TIM4, //TIM2
		TIM_IT_Update ,
		ENABLE  //使能
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM4, ENABLE);  //使能TIMx外设
							 
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
	  //模式0
				if(flag_mode==0)
				{
				 TIM_SetCompare1(TIM3,1350);
		     TIM_SetCompare2(TIM3,1450);
				}
				
		//模式1
				if(flag_mode==1)
				{
				  TIM_SetCompare1(TIM3,1350+PID_control_X(94));
		      TIM_SetCompare2(TIM3,1480+PID_control_Y(103));
				}
				
	 //模式2
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
				
				
	 //模式3
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
	  //模式4	
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











