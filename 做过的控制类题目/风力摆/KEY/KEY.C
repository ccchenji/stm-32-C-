#include "KEY.H"
#include "delay.h"
void delay_ms1(unsigned int i)
{
   unsigned int j;
   for( ;i>0;i--)
   {
      for(j=110;j>0;j--);
   }
}
void KEY_Init(void)
{
	  GPIO_InitTypeDef GPIO_Initstruct;
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	  GPIO_Initstruct.GPIO_Mode=GPIO_Mode_IPU;
	  GPIO_Initstruct.GPIO_Pin=GPIO_Pin_4;
	  GPIO_Init(GPIOB,&GPIO_Initstruct);
	
	  GPIO_Initstruct.GPIO_Mode=GPIO_Mode_IPU;
	  GPIO_Initstruct.GPIO_Pin=GPIO_Pin_5;
	  GPIO_Init(GPIOB,&GPIO_Initstruct);
	
	  GPIO_Initstruct.GPIO_Mode=GPIO_Mode_IPU;
	  GPIO_Initstruct.GPIO_Pin=GPIO_Pin_3;
	  GPIO_Init(GPIOA,&GPIO_Initstruct);
}

int KEY_Scan()
{
	if(KEY1==0||KEY2==0||KEY3==0)
	{
		 delay_ms1(5);
		 if(KEY1==0) return 1;
		 if(KEY2==0) return 2;
		 if(KEY3==0) return 3;
	} 
	return 0;
}




























