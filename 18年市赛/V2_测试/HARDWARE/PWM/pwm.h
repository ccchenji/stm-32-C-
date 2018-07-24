#ifndef __PWM_H
#define __PWM_H
#include "sys.h"



void TIM1_PWM_Init(u16 arr,u16 psc);
void TIM6_Init(u16 arr,u16 psc);

void PWM1_CH1(int i);
void PWM1_CH2(int i);
void PWM1_CH3(int i);
void PWM1_CH4(int i);

void Move(short L_Speed,short R_Speed);

#endif
