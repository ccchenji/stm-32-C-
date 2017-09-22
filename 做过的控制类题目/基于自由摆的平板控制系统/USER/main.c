#include "stm32f10x.h"
#include "delay.h"
#include "adc.h"
#include "timer.h"
#include "driver.h"
#include "OLED.H"
#include "ADC_filter.h"
#include "sys.h"
#include "usart.h"	
#include "math.h"
#include "KEY.H"
#include "mpuiic.h"
#include "Balance.h"
#include "mpu6050.h"
#include "report.h"
void My_DelayMs(u16 time);
float My_Angle=0;
float lvboqian,lvbohou;
extern float value_buf[];
extern float shedingjiao;
extern float aerfa;
float N_Gyro_Y;
float yuzhou;
int main(void)
{
	short a=0;
  delay_init();	    	 //��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	uart_init(9600);
	OLED_Init();
	Adc_Init();
  Driver_Init();
	MPU_Init();
	MPU_IIC_Init();
  TIM1_OPM_RCR_Init(999,72-1); //1MHz����Ƶ��  ������+�ظ�����ģʽ
	TIM4_Int_Init(19,7199);//��ʱ20ms	
	for(a=0;a<10;a++)
	{
		 value_buf[a]=Get_Adc(ADC_Channel_1);
	}
  while(1)
	 {	  	
			  if(My_Angle>0)   
					 {  
						shedingjiao=My_Angle+aerfa;
						 if(Real_sum_Err_My_angle>0)
						 {
						 if(shedingjiao-shedingjiao_save>0)
						 {
								shedingjiao_save=shedingjiao;
						 }
						 	Locate_Abs(shedingjiao_save/0.0072,100000);
					   }
						 if(Real_sum_Err_My_angle<0)
						 {
							  if(shedingjiao-shedingjiao_save<0)
						 {
								shedingjiao_save=shedingjiao;
						 } 
						 Locate_Abs(shedingjiao_save/0.0072,100000);
						 } 
			     }
			  if(My_Angle<0) 
					{
						shedingjiao=My_Angle+aerfa;
						 if(Real_sum_Err_My_angle<0)
						 {
							  if(shedingjiao-shedingjiao_save1<0)
								{
									 	shedingjiao_save1=shedingjiao;
								}
							 Locate_Abs(shedingjiao_save1/0.0072+100,90000); 	
						 }
						 if(Real_sum_Err_My_angle>0)
						 {
							   if(shedingjiao-shedingjiao_save1>0)
								{
									 	shedingjiao_save1=shedingjiao;
								}
							 Locate_Abs(shedingjiao_save1/0.0072+100,90000); 	
						 }						
				  } 
		  I_send_data(0,0,(short)My_Angle);//���Զ���֡����ԭʼ����
   }
}
void My_DelayMs(u16 time)
{
	 u16 i=0;
	while(time--)
	{
		i=12000;
		while(i--);
	}
}

