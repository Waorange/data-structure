#include "Queue.h"

void QueueInit(Queue * Q)
{
	Q->_head = NULL;
	Q->_tail = NULL;
}
void QueuePush(Queue * Q, Datatype x)
{
	QueueNode * Node = (QueueNode *)malloc(sizeof(QueueNode));
	Node->_data = x;
	Node->next = NULL;
	if (Q->_head != NULL)
	{
		Q->_tail->next = Node;
		Q->_tail = Q->_tail->next;
	}
	else
	{
		Q->_head = Node;
		Q->_tail = Node;
	}
}

void QueuePop(Queue * Q)
{
	if (!QueueEmpty(Q))
	{
		Q->_head = Q->_head->next;
	}
}

int QueueEmpty(Queue * Q)
{
	if (Q->_head != NULL)
	{
		return 0;
	}
	return 1;
}

Datatype QueueFront(Queue * Q)
{
	assert(Q);
	return Q->_head->_data;
}
size_t Queuesize(Queue * Q)
{
	int count = 0;
	QueueNode * cur = Q->_head;
	if (!QueueEmpty(Q))
	{
		while (cur != NULL)
		{
			count++;
			cur = cur->next;
		}
	}
	return count;
}
