#ifndef _AD_H
#define _AD_H
#include "reg51.h"
#include "intrins.h"
sfr   ADC_CONTR   =0XBC;//ADC的控制寄存器
sfr   ADC_RES     =0XBD;//存储高位数据
sfr   ADC_RESL    =0XBE;//存储底位数据
sfr   P1ASF       =0X9D;//可通过软件设置P1口的任意一路设为A/D转换;
sfr   AUXR1       =0XA2;						 
void InitADC();
int AD_get();

#endif