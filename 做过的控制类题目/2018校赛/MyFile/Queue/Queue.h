#ifndef _Queue_H
#define _Queue_H
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct queue
{
	int a[10]; //队列长度
	int last;  //队尾
	int first; //对首
} Queue;

int IsEmpty(Queue queue);
int IQueue(Queue *queue, int data);
int OQueue(Queue *queue);


#endif
