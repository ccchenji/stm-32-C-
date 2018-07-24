#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "dma.h"
#include "led.h"
#define num_measure_distance 14 //红外个数
/*
管脚说明：
电机输出   左A8 A9  右A10 A11
红外测距   
灰度       
*/
void DMA1_Channel1_IRQHandler(void);
void Move(short L_Speed,short R_Speed);
u16 value[num_measure_distance];
u16 head[3],left_HW[3],right_HW[3],End_HW;

int main(void)
{
	
	delay_init();	
	LED_Init();KEY_Init();BEEP_Init();
	//MYDMA_Config(DMA1_Channel1,(u32)&ADC1->DR,(u32)&value,num_measure_distance);//初始化DMA
	//Adc_Init();
	//TIM1_PWM_Init(1799,0); 
	NVIC_Configuration();
	SOLGUI_Init(&FirstPage);
	 while(1)
	{
	SOLGUI_InputKey(Get_Key());
    SOLGUI_Menu_PageStage();
	delay_ms(100);
    SOLGUI_Refresh();
	}
}

