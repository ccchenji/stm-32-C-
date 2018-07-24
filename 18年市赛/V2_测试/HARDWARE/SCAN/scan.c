#include "scan.h"
#include "delay.h"
void mm_scan_GPIO_Config(void)	
{

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); // 使能PC端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_15;	//选择对应的引脚//GPIO_Pin_0|
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  //初始化PC端口

 
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE); // 使能PC端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;	//选择对应的引脚//GPIO_Pin_0|
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  //初始化PC端口
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE); // 使能PC端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//选择对应的引脚//GPIO_Pin_0|
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  //初始化PC端口


}

u8 mm_scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{			
		
   
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == mm_OFF ) 
	  	  
		return mm_OFF;
		
	else
		return mm_ON;
}

