#ifndef _AD_H
#define _AD_H
#include "reg51.h"
#include "intrins.h"
sfr   ADC_CONTR   =0XBC;//ADC�Ŀ��ƼĴ���
sfr   ADC_RES     =0XBD;//�洢��λ����
sfr   ADC_RESL    =0XBE;//�洢��λ����
sfr   P1ASF       =0X9D;//��ͨ���������P1�ڵ�����һ·��ΪA/Dת��;
sfr   AUXR1       =0XA2;
void InitADC();						   				
float AD_get();

#endif