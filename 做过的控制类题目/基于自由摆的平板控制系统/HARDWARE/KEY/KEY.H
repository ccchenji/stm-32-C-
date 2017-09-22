#ifndef _KEY_H
#define _KEY_H
#include "sys.h"

#define KEY1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)
#define KEY2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)
#define KEY3 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)
#define KEY4 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)

void KEY_Init(void);
int KEY_Scan(void);


#endif

