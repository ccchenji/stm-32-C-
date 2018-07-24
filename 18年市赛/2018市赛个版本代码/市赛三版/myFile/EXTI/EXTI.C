#include "EXTI.H"
#include "delay.h"
void EXTIX_INIT()
{
	GPIO_InitTypeDef GPIO_Initstruct;
	EXTI_InitTypeDef EXTI_Initstrue;
	NVIC_InitTypeDef NVIC_Initstrue;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	GPIO_Initstruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Initstruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOB, &GPIO_Initstruct);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);

	GPIO_Initstruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Initstruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_Initstruct);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);

	EXTI_Initstrue.EXTI_Line = EXTI_Line0;
	EXTI_Initstrue.EXTI_LineCmd = ENABLE;
	EXTI_Initstrue.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Initstrue.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_Initstrue);

	EXTI_Initstrue.EXTI_Line = EXTI_Line1;
	EXTI_Initstrue.EXTI_LineCmd = ENABLE;
	EXTI_Initstrue.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Initstrue.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_Initstrue);

	NVIC_Initstrue.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_Initstrue.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Initstrue.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_Initstrue.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_Initstrue);

	NVIC_Initstrue.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_Initstrue.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Initstrue.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_Initstrue.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_Initstrue);
}
