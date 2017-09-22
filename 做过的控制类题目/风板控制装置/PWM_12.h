#ifndef PWM_12_H_
#define PWM_12_H_
#include <reg51.h>
#include <intrins.h>
#define FOCS 18432000L
void PWM_change(unsigned char a);
/*Declare SFR associated with the PCA*/
sfr    CCON     =0XD8;
sbit   CCF0     =CCON^0;
sbit   CCF1     =CCON^1;
sbit   CR       =CCON^6;
sbit   CF       =CCON^7;
sfr    CMOD     =0XD9;
sfr    CL       =0XE9;
sfr    CH       =0XF9;
sfr    CCAPM0   =0XDA;
sfr    CCAP0L   =0XEA;
sfr    CCAP0H   =0XFA;
sfr    CCAPM1   =0XDB;
sfr    CCAP1L   =0XEB;
sfr    CCAP1H   =0XFB;
sfr    PCAPWM0  =0XF2;
sfr    PCAPWM1  =0XF3;

#endif