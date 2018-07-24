#include "key.h"
void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);//使能GPIOB时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
  GPIO_Init(GPIOD, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
	
}
int KEY_Scan()
{
	if (KEY1 == 0 || KEY2 == 0 || KEY3 == 0 || KEY4 == 0|| KEY5==0|| KEY6==0)
	{
		delay_ms(30);
		if (KEY1 == 0) return 3;//左键
		if (KEY2 == 0) return 2;//下键
		if (KEY3 == 0) return 4;//右键
		if (KEY4 == 0) return 5;//确认
		if (KEY5 == 0) return 1;//上键
		if (KEY6 == 0) return 6;//返回
	}
	return 0;
}











