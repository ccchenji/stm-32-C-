#ifndef _KEY_H
#define _KEY_H
#include "sys.h"

#define KEY1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)
#define KEY2 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)
#define KEY3 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)

void KEY_Init(void);
int KEY_Scan(void);


#endif

