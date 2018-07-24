#include "led.h"
#include "delay.h"
#define READ_KEY_1  GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_9)
#define READ_KEY_2  GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10)
#define READ_KEY_3  GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12)
#define READ_KEY_4  GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_8)
#define READ_KEY_5  GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_11)
#define READ_KEY_6  GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13)
#define LED6 PBout(13)
#define LED7 PBout(14)
#define LED8 PBout(15)
#define LED9 PBout(12)
#define YES_1 0
void LED_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PA,PD端口时钟
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //LED0-->PA.8 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);
 GPIO_SetBits(GPIOB,GPIO_Pin_13);
}
 
void KEY_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);//使能GPIOB时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
  GPIO_Init(GPIOD, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
}

void BEEP_Init(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
GPIO_Init(GPIOD, &GPIO_InitStructure); 
GPIO_ResetBits(GPIOD,GPIO_Pin_7); 
}

uint8_t Get_Key(void)
{
    if(READ_KEY_1 == YES_1 || READ_KEY_2 == YES_1 || READ_KEY_3 == YES_1 || READ_KEY_4 == YES_1 || READ_KEY_5 == YES_1 || READ_KEY_6 == YES_1)
    {
				BEEP=1;
        delay_ms(20);	
				BEEP=0;
        if(READ_KEY_1 == YES_1) return KEY_1;
        else if(READ_KEY_2 == YES_1) return KEY_2;
        else if(READ_KEY_3 == YES_1) return KEY_3;
        else if(READ_KEY_4 == YES_1) return KEY_4;
        else if(READ_KEY_5 == YES_1) return KEY_5;
        else if(READ_KEY_6 == YES_1) return KEY_6;
    }
    return 0;
}
