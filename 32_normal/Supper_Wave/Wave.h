#ifndef _Wave_H
#define _Wave_H
#include "stm32f10x.h"
#include "sys.h"
#define Trig_H  GPIO_SetBits(GPIOA,GPIO_Pin_5);	
#define Trig_L  GPIO_ResetBits(GPIOA,GPIO_Pin_5);	
#define Echo    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//¶ÁÈ¡IO¿ÚµÄ×´Ì¬

void Wave_Init(void);
float Wave_star(void);


#endif

