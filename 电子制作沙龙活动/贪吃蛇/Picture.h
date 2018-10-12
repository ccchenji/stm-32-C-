#ifndef _Picture_H
#define _Picture_H
#include "reg52.h"
#include<intrins.h>
#include "interruption.h"
typedef unsigned int u16;  //对数据类型进行声明定义
typedef unsigned char u8;
void delay(u16 i);
void Hc595SendByte(u8 dat);
void DrawPoint(u8 x,u8 y);
void pattren(u8 roll[8]);
void char_roll(u8 roll[],short num);


#endif