#include "key.h"
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_Initstruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	
	GPIO_Initstruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Initstruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOA, &GPIO_Initstruct);

	GPIO_Initstruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Initstruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA, &GPIO_Initstruct);

	GPIO_Initstruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Initstruct.GPIO_Pin =GPIO_Pin_13|GPIO_Pin_12|GPIO_Pin_8| GPIO_Pin_9;
	GPIO_Init(GPIOB, &GPIO_Initstruct);
	
}
int KEY_Scan()
{
	if (KEY1 == 0 || KEY2 == 0 || KEY3 == 0 || KEY4 == 0|| KEY5==0|| KEY6==0)
	{
		delay_ms(60);
		if (KEY1 == 0) return 1;
		if (KEY2 == 0) return 2;
		if (KEY3 == 0) return 3;
		if (KEY4 == 0) return 4;
		if (KEY5 == 0) return 5;
		if (KEY6 == 0) return 6;
	}
	return 0;
}











