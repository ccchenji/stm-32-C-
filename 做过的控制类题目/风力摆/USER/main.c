#include "sys.h"
#include "OLED.H"
#include "usart.h"		
#include "delay.h"	   
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "stm32f10x.h"
#include "pwm.h"
#include "timer.h"
#include "KEY.H"
#include "report.h"
#include "math.h"
extern float long_roll;
extern double Set_Anglex;
extern double Set_Angley;
extern float roll;
extern float pitch;
 int main(void)
 { 
	   int i=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 	//串口初始化为9600
	MPU_Init();					//初始化MPU6050
	mpu_dmp_init();
	OLED_Init();			//初始化OLED  
	OLED_Clear(); 
	KEY_Init();
	TIM4_Int_Init(7199,79);
  TIM3_PWM_Init(3599,0);
	TIM2_PWM_Init(3599,0);
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare3(TIM2,0);
	TIM_SetCompare1(TIM3,0);
	TIM_SetCompare2(TIM2,0);
 	while(1)
	{
		//I_send_data(pitch,Set_Anglex);
//		I_send_data(roll,Set_Angley);
//		if(roll>0)
//		{
		OLED_ShowNum(0,0,70*tan(roll),2,16);
//		}
		printf("%f",roll);
		printf("\r\n");
	}
}
 


