#include "stack.h"
int StackIsEmpty(MyStack stack)//判断栈是否为空
{
	return stack.top == -1;
}
int Push(MyStack *stack, Var data)//进栈函数
{
	int size = sizeof(stack->data) / sizeof(stack->data[0]);//得到数组的长度
	if (stack->top < 9)
	{
		stack->top++;
		stack->data[stack->top].all_Line = data.all_Line;//数据进栈
		stack->data[stack->top].page_skewing = data.page_skewing;//数据进栈
		stack->data[stack->top].set_y = data.set_y;//数据进栈
		return 1;//进栈成功
	}
	else
	{
		return 0;//进栈失败
	}
}
int Pop(MyStack *stack, Var *data)//出栈函数
{
	if (!StackIsEmpty(*stack))//判断栈是否为空
	{
		data->all_Line = stack->data[stack->top].all_Line;
		data->set_y = stack->data[stack->top].set_y;
		data->page_skewing = stack->data[stack->top--].page_skewing;
		return 1;//出栈成功
	}
	else
	{
		return 0;//进栈成功
	}
}