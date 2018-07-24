#ifndef  _stack_H
#define  _stack_H
#include <stdio.h>
#include "menu.h"
typedef Mycourse Var;//定义变量类型
typedef struct _stack
{
	Var data[10];//定义空间的大小
	int top;//栈指针
}MyStack;

int StackIsEmpty(MyStack stack);//判断栈是否为空
int Push(MyStack *stack, Var data);//进栈函数
int Pop(MyStack *stack, Var *data);//出栈函数

#endif 

