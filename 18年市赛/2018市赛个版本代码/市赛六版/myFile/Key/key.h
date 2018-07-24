#ifndef _key_H
#define _key_H
#include "sys.h"
#include "delay.h"

#define KEY1 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_9)
#define KEY2 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10)
#define KEY3 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12)
#define KEY4 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_8)
#define KEY5 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_11)
#define KEY6 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13)

void KEY_Init(void);
int KEY_Scan(void);


#endif

