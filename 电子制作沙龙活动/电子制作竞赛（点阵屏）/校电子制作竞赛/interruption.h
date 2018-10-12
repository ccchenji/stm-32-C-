#ifndef _interruption_H
#define _interruption_H
#include <reg51.h>
void delay_ms(unsigned int i);
void Int0Init();
void Int1Init();
void Timer0Init();
void Timer1Init();
void UsartInit();
#endif
