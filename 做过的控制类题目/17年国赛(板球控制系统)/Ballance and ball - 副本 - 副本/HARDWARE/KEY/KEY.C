#include "KEY.H"
void KEY_Init(void)
{
	  GPIO_InitTypeDef GPIO_Initstruct;
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	  GPIO_Initstruct.GPIO_Mode=GPIO_Mode_IPU;
	  GPIO_Initstruct.GPIO_Pin=GPIO_Pin_1;
	  GPIO_Init(GPIOA,&GPIO_Initstruct);
	
	  GPIO_Initstruct.GPIO_Mode=GPIO_Mode_IPU;
	  GPIO_Initstruct.GPIO_Pin=GPIO_Pin_2;
	  GPIO_Init(GPIOA,&GPIO_Initstruct);
	
	  GPIO_Initstruct.GPIO_Mode=GPIO_Mode_IPU;
	  GPIO_Initstruct.GPIO_Pin=GPIO_Pin_3;
	  GPIO_Init(GPIOA,&GPIO_Initstruct);
	
	  GPIO_Initstruct.GPIO_Mode=GPIO_Mode_IPU;
	  GPIO_Initstruct.GPIO_Pin=GPIO_Pin_4;
	  GPIO_Init(GPIOA,&GPIO_Initstruct);
}
short KEY_Scan()
{
	if(KEY1==0||KEY2==0||KEY3==0||KEY4==0)
	{
		 delay_ms(30);
		 if(KEY1==0) return 1;
		 if(KEY2==0) return 2;
		 if(KEY3==0) return 3;
		 if(KEY4==0) return 4;
	} 
	return 0;
}











