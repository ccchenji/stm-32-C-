#include "EXTI.H"
#include "delay.h"
int flag_AA = 1, flag_BB = 1;//对编码器的值进行简单的滤波
int num_code = 0;//编码器的值
void EXTIX_INIT()
{
	GPIO_InitTypeDef GPIO_Initstruct;
	EXTI_InitTypeDef EXTI_Initstrue;
	NVIC_InitTypeDef NVIC_Initstrue;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//禁用JATG才能使用PB^3和PB^4

	GPIO_Initstruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Initstruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOB, &GPIO_Initstruct);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource3);

	GPIO_Initstruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Initstruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOB, &GPIO_Initstruct);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource4);

	EXTI_Initstrue.EXTI_Line = EXTI_Line3;
	EXTI_Initstrue.EXTI_LineCmd = ENABLE;
	EXTI_Initstrue.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Initstrue.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_Initstrue);

	EXTI_Initstrue.EXTI_Line = EXTI_Line4;
	EXTI_Initstrue.EXTI_LineCmd = ENABLE;
	EXTI_Initstrue.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Initstrue.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_Initstrue);

	NVIC_Initstrue.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_Initstrue.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Initstrue.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_Initstrue.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_Initstrue);

	NVIC_Initstrue.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_Initstrue.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Initstrue.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_Initstrue.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_Initstrue);
}
//-----------------------中断处理------------------------------
void EXTI3_IRQHandler(void)
{
	if (flag_AA == 1)
	{
		if (B_Input() == 0)
		{
			num_code--;
		}
		else
		{
			num_code++;
		}
		flag_AA = 0; flag_BB = 1;
	}
	EXTI_ClearITPendingBit(EXTI_Line3);  //清除EXTI3线路挂起位
}

void EXTI4_IRQHandler(void)
{
	if (flag_BB == 1)
	{
		flag_AA = 1;
		flag_BB = 0;
	}
	EXTI_ClearITPendingBit(EXTI_Line4);  //清除EXTI4线路挂起位
}

