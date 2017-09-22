#include "timer.h"
#include "control.h"
#include "math.h"
#include "key.h"
#include "inv_mpu.h"
#include "math.h"
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
//这里时钟选择为APB1的2倍，而APB1为36
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
int flag=1;
double t=0;
int Angle=0;
double Set_Angley=30;
double Set_Anglex=35;
float rangeII=35.0;//模式II的幅值
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
void TIM4_IRQHandler(void)   //TIM4中断
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
 /****************模式Iok********************/  
			mpu_dmp_get_data(&pitch,&roll,&yaw);
			long_roll=tan((roll)*3.14/180)*98.5;	
			long_pitch=tan((pitch+3)*3.14/180)*80;
			if(flag==0)
		{
			 PID_change1(240,6300,0);//1100，1400000，5   260   6300
	   	 PID_change2(260,6000,0);//2100，1400000，5
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
 /****************模式IIok**********************/
				if(flag==1)
		{
			 PID_change1(60,100,0);//1100，1400000，5   240   6300
	   	 PID_change2(60,100,0);//2100，1400000，5   260   6000
			 
			if(rangeII>40&&rangeII<=50)
			 {
				  PID_change1(200,630,0);//1100，1400000，5   260   6300
	   	    PID_change2(200,600,0);//2100，1400000，5
			 }
			 if(rangeII>50)
			 {
				  PID_change1(180,630,0);//1100，1400000，5   260   6300
	   	    PID_change2(180,600,0);//2100，1400000，5
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
 /******************模式III*********************/
		if(flag==2)
		{			  
			 PID_change1(1100,1400000,5);//1100，1400000，5   260   6300
	   	 PID_change2(2100,1400000,5);//2100，1400000，5
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
/*******************模式IVok************************/
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
/*******************模式V***********************/
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
		    TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
}










