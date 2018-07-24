#include "Queue.h"
//判断空对或对满状态
int IsEmpty(Queue queue)
{
	int b = sizeof(queue.a) / sizeof(queue.a[0]); //得到数组的大小
	if (queue.last == queue.first)
		return 1; //队列为空
	if ((queue.last + 1) % b == queue.first)
		return 0; //队列为满
	return 2;
}
//进队操作
int IQueue(Queue *queue, int data)
{
	int b = sizeof(queue->a) / sizeof(queue->a[0]);
	if (!IsEmpty(*queue))
		return 0; //进队失败
	queue->a[queue->last] = data;        //进队
	queue->last = (queue->last + 1) % b; //队尾加一
	return 1;                            //进对成功
}
//出队操作
int OQueue(Queue *queue)
{
	int b = 0;
	int data = 0;
	if (IsEmpty(*queue) == 1)
		return 0;                                   //出队失败
	b = sizeof(queue->a) / sizeof(queue->a[0]); //得到数组的长度
	data = queue->a[queue->first];              //得到数据
	queue->first = (queue->first + 1) % b;          //队首加一
	return data;
}
