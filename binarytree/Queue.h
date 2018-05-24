#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct BinaryNode* Datatype;
typedef struct QueueNode{
	Datatype _data;
	struct QueueNode *next;
}QueueNode;

typedef struct Queue {
	QueueNode * _head;
	QueueNode * _tail;
}Queue;

void QueueInit(Queue * Q);
void QueuePop(Queue * Q);
void QueuePush(Queue * Q, Datatype x);
int QueueEmpty(Queue * Q);
Datatype QueueFront(Queue * Q);
size_t Queuesize(Queue * Q);


#endif // !#_QUEUE_H_
