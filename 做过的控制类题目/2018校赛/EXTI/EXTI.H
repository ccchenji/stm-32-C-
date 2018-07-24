#ifndef _EXTI_H
#define _EXTI_H
#include "stm32f10x.h"

#define A_Input() GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)//得到Io口的状态
#define B_Input() GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)

void EXTIX_INIT(void);




#endif