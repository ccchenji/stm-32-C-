#include "timer.h"
#include "PID.h"
#include "OLED.H"
#include "text.h"
extern short fps;
char flag=0;
int timer=0;
short My_timer=0;

char flag_mode=0;
extern float err_X;
extern float err_Y;
short SET_DATE[13][2]={{164,29},{169,100},{169,172},{93,30},{94,103},{96,178},{22,34},
                               {21,106},{24,177},{131,65},{134,138},{56,65},{58,140}};
short MODEII_timer=0;
short MODEII_flag=0;

short MODEIII_flag=0;
short MODEIII_timer=0;

short MODEVI_flag=0;
short MODEVI_timer=0;
															 
short MODEV_flag=0;														 
short MODEV_timer=0;

short MODEIV_flag=0;
short MODEIV_timer=0;	

short MODEVII_flag=0;
short MODEVII_timer=0;															 

//查找路径的参数														 
short place_save[16][2]={0};	
short area_save=0;
char count_n=0;
char count_w=0;
short Real_area=0;

char  A_flag=1;
char  B_flag=1;
char  C_flag=1;
char  D_flag=1;		


//FLASH相关的参数

u16  x_smoth=1450;
u16  y_smoth=1380;
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
			
	   //计时器
			   if(flag==1)
				 {
			      timer++;
				 }
	  //模式0
				if(flag_mode==0)
				{
				   TIM_SetCompare1(TIM3,x_smoth);
		       TIM_SetCompare2(TIM3,y_smoth);
				   flag=0;
				}
			
		//模式1
				if(flag_mode==1)
				{
				  TIM_SetCompare1(TIM3,x_smoth+PID_control_X(SET_DATE[4][0]));
		      TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(SET_DATE[4][1]));
				 //计数部分
						if(err_X<=10&&err_X>=-10&&err_Y>=-10&&err_Y<=10)
					 {
						  My_timer++;
						if(My_timer>=250)
						{
					      flag=0;
							  My_timer=250;
						}
					 }
					else
					 {
						  My_timer=0;
						  flag=1;
					 }
				}
				
	 //模式2
				if(flag_mode==2)
				{
					 
					if(err_X<=4&&err_X>=-4&&err_Y>=-4&&err_Y<=4)
					{
			       MODEII_flag=1;
					}
					else
					{
						 MODEII_flag=0;
						 flag=1;
					}
					if(MODEII_flag==1)
					{
						  MODEII_timer++;
						 if(MODEII_timer>=400)
						 {
							  MODEII_timer=400;
						 }
					}
					if(MODEII_timer<=300)
					{
					  TIM_SetCompare1(TIM3,x_smoth+PID_control_X(SET_DATE[3][0]));
		        TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(SET_DATE[3][1]));
					}
					else
					{
						 TIM_SetCompare1(TIM3,x_smoth+PID_control_X(SET_DATE[4][0]));
		         TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(SET_DATE[4][1]));
					//计数部分
						if(err_X<=4&&err_X>=-4&&err_Y>=-4&&err_Y<=4)
						{
							  My_timer++;
								if(My_timer>=200)
						  {
					       flag=0;
							   My_timer=200;
					   	}
						}
						else
						{
							 My_timer=0;
						   flag=1;
						}
					}
				}
				
				
	 //模式3
				if(flag_mode==3)
				{
					 if(MODEIII_flag==0)
					 {
					   TIM_SetCompare1(TIM3,x_smoth+PID_control_X(SET_DATE[9][0]));
		         TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(SET_DATE[9][1]));
					 }
					 if(MODEIII_flag==1)
					 {
								TIM_SetCompare1(TIM3,x_smoth+PID_control_X(SET_DATE[11][0]));
		            TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(SET_DATE[11][1]));
					 }
					 if(MODEIII_flag==2)
					 {
						   TIM_SetCompare1(TIM3,x_smoth+PID_control_X(SET_DATE[12][0]));
		           TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(SET_DATE[12][1]));
					 }
					 if(MODEIII_flag==3)
					 {
						  TIM_SetCompare1(TIM3,x_smoth+PID_control_X(SET_DATE[8][0]));
		          TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(SET_DATE[8][1]));
						  //计数部分
             	if(err_X<=4&&err_X>=-4&&err_Y>=-4&&err_Y<=4)
						 {
							  My_timer++;
								if(My_timer>=200)
						   {
					       flag=0;
							   My_timer=200;
					   	 }
						 }
						  else
						  {
							   My_timer=0;
						     flag=1;
						  }				 
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
										 MODEIII_timer=100;
									 }
					 }
					 else
					 {
						   MODEIII_timer=0;
						   flag=1;
					 }
				}
	  //模式4	
		  if(flag_mode==4)
			{
				 if(MODEVI_flag==0)
				 {
					   TIM_SetCompare1(TIM3,x_smoth+PID_control_X(SET_DATE[1][0]));
		         TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(SET_DATE[1][1]));
				 }
				 if(MODEVI_flag==1)
				 {
					   TIM_SetCompare1(TIM3,x_smoth+PID_control_X(SET_DATE[5][0]));
		         TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(SET_DATE[5][1]));
				 }
				 if(MODEVI_flag==2)
				 {
					   TIM_SetCompare1(TIM3,x_smoth+PID_control_X(SET_DATE[8][0]));
		         TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(SET_DATE[8][1]));
					   //计数部分
					   	if(err_X<=4&&err_X>=-4&&err_Y>=-4&&err_Y<=4)
						{
							  My_timer++;
								if(My_timer>=200)
						  {
					       flag=0;
							   My_timer=200;
					   	}
						}
						else
						{
							 My_timer=0;
						   flag=1;
						}
				 }
				if(err_X<=10&&err_X>=-10&&err_Y>=-10&&err_Y<=10)
				{
					 MODEVI_timer++;
					 if(MODEVI_timer>=200)
					 {
						  MODEVI_flag++;
						 if(MODEVI_flag>=2)
						 {
							  MODEVI_flag=2;
						 }
						 MODEVI_timer=200;
					 }
				}
				else
				{
					 MODEVI_timer=0;
					 flag=1;
				}
			}
			
		  //模式5
			if(flag_mode==5)
			{
				  if(MODEV_flag==0||MODEV_flag==4||MODEV_flag==8||MODEV_flag==12)
					{
						 TIM_SetCompare1(TIM3,x_smoth+PID_control_X(SET_DATE[9][0]));
		         TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(SET_DATE[9][1]));
					}
					if(MODEV_flag==1||MODEV_flag==5||MODEV_flag==9||MODEV_flag==13)
					{
						 TIM_SetCompare1(TIM3,x_smoth+PID_control_X(SET_DATE[10][0]));
		         TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(SET_DATE[10][1]));
					}
					if(MODEV_flag==2||MODEV_flag==6||MODEV_flag==10||MODEV_flag==14)
					{
						 TIM_SetCompare1(TIM3,x_smoth+PID_control_X(SET_DATE[12][0]));
		         TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(SET_DATE[12][1]));
					}
					if(MODEV_flag==3||MODEV_flag==7||MODEV_flag==11)
					{
						 TIM_SetCompare1(TIM3,x_smoth+PID_control_X(SET_DATE[11][0]));
		         TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(SET_DATE[11][1]));
					}
					if(MODEV_flag==15)
					{
						 TIM_SetCompare1(TIM3,x_smoth+PID_control_X(SET_DATE[8][0]));
		         TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(SET_DATE[8][1]));
						  //计数部分
					   	if(err_X<=4&&err_X>=-4&&err_Y>=-4&&err_Y<=4)
						{
							  My_timer++;
								if(My_timer>=200)
						  {
					       flag=0;
							   My_timer=200;
					   	}
						}
						else
						{
							 My_timer=0;
						   flag=1;
						}
					}			
					if(err_X<=10&&err_X>=-10&&err_Y>=-10&&err_Y<=10)
					{
							  MODEV_timer++;
						 if(MODEV_timer>=50)
					   {
						    MODEV_flag++;
						   if(MODEV_flag>=15)
						   {
							   MODEV_flag=15;
						   }
							 MODEV_timer=50;
					   }
					}
					   else
						{
							 MODEV_timer=0;
							 flag=1;
						}			
			}
			//模式6
			if(flag_mode==6)
			{
			  //通过计算得到路径
				if(MODEIV_flag==1)
			 {
				 find_way(A_flag,B_flag);
				for(count_w=0;count_w<need_area;count_w++)
				{
					  for(count_n=0;count_n<2;count_n++)
						{
							 place_save[area_save+count_w][count_n]=aim_area[count_w][count_n];
						}
				}
				 area_save=need_area+area_save;
				 find_way(B_flag,C_flag);
				for(count_w=0;count_w<need_area;count_w++)
				{
					  for(count_n=0;count_n<2;count_n++)
						{
							 place_save[area_save+count_w][count_n]=aim_area[count_w][count_n];
						}
				}
				 area_save=need_area+area_save;
				 find_way(C_flag,D_flag);
				for(count_w=0;count_w<need_area;count_w++)
				{
					  for(count_n=0;count_n<2;count_n++)
						{
							 place_save[area_save+count_w][count_n]=aim_area[count_w][count_n];
						}
				}
				 area_save=need_area+area_save;
				 flag=1;
			 }
				 MODEIV_flag=0;
				 TIM_SetCompare1(TIM3,x_smoth+PID_control_X(place_save[Real_area][0]));
		     TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(place_save[Real_area][1]));
			   if(Real_area==area_save-1)
				 {
					    if(err_X<=4&&err_X>=-4&&err_Y>=-4&&err_Y<=4)
							{
									My_timer++;
								 if(My_timer>=200)
						    {
					       flag=0;
							   My_timer=200;
					     	}
							}
							else
							{
								 My_timer=0;
						     flag=1;
							}
				 }
				  if(err_X<=10&&err_X>=-10&&err_Y>=-10&&err_Y<=10)
					{
						 MODEIV_timer++;
						 if(MODEIV_timer>=200)
						 {
							 Real_area++;
							 if(Real_area>=area_save)
							 {
								  Real_area=area_save-1;
							 }
							 MODEIV_timer=200;
						 }
					}
					else
					{
						  MODEIV_timer=0;
					}
				
			}
			
   //模式7自由发挥部分
			  if(flag_mode==7)
				{
					 if(MODEVII_flag==0)
					 {
						 TIM_SetCompare1(TIM3,x_smoth+PID_control_X(SET_DATE[1][0]));
		         TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(SET_DATE[1][1]));
					 }
					 if(MODEVII_flag==1)
					 {
						 TIM_SetCompare1(TIM3,x_smoth+PID_control_X(SET_DATE[5][0]));
		         TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(SET_DATE[5][1]));
					 }
					 if(MODEVII_flag==2)
					 {
						 TIM_SetCompare1(TIM3,x_smoth+PID_control_X(SET_DATE[4][0]));
		         TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(SET_DATE[4][1]));
					 }
					 if(MODEVII_flag==3)
					 {
						 TIM_SetCompare1(TIM3,x_smoth+PID_control_X(SET_DATE[3][0]));
		         TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(SET_DATE[3][1])); 
					 }
					 if(MODEVII_flag==4)
					 {
						 TIM_SetCompare1(TIM3,x_smoth+PID_control_X(SET_DATE[7][0]));
		         TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(SET_DATE[7][1])); 
					 }
					 if(MODEVII_flag==5)
					 {
						 TIM_SetCompare1(TIM3,x_smoth+PID_control_X(SET_DATE[5][0]));
		         TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(SET_DATE[5][1])); 
					 }
					 if(MODEVII_flag==6)
					 {
						 TIM_SetCompare1(TIM3,x_smoth+PID_control_X(SET_DATE[4][0]));
		         TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(SET_DATE[4][1]));
					 }
					 if(MODEVII_flag==7)
					 {
						 TIM_SetCompare1(TIM3,x_smoth+PID_control_X(SET_DATE[3][0]));
		         TIM_SetCompare2(TIM3,y_smoth+PID_control_Y(SET_DATE[3][1]));
						  //计数部分
					   	if(err_X<=4&&err_X>=-4&&err_Y>=-4&&err_Y<=4)
						{
							  My_timer++;
								if(My_timer>=150)
						  {
					       flag=0;
							   My_timer=200;
					   	}
						}
						else
						{
							 My_timer=0;
						   flag=1;
						}
					 }
					 if(err_X<=10&&err_X>=-10&&err_Y>=-10&&err_Y<=10)
					{
							  MODEVII_timer++;
						 if(MODEVII_timer>=150)
					   {
						    MODEVII_flag++;
						   if(MODEVII_flag>=7)
						   {
							   MODEVII_flag=7;
						   }
							 MODEVII_timer=150;
					   }
					}
					   else
						{
							 MODEVII_timer=0;
							 flag=1;
						}			
				}
		    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  
		}
}











