#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//ͨ�ö�ʱ�� ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/12/03
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  


void TIM4_Int_Init(u16 arr,u16 psc);
void TIM3_Int_Init(u16 arr,u16 psc);
extern float L;
extern float X;
extern float aerfa;
extern float shedingjiao;
extern float shedingjiao_save ;
extern float shedingjiao_save1;
extern float My_Angle_save ;
extern short flag;
extern float Err_My_angle;
extern short flag_way;
extern float  sum_Err_My_angl;
extern float Real_sum_Err_My_angle; 
#endif
