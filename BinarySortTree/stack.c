#include "stack.h"

void StackInit(Stack * S, int x)
{
	S->capcity = x;
	S->_array = (Datatype *)malloc(sizeof(Datatype) * S->capcity);
	S->top = 0;
	S->base = 0;
}

//如果栈空返回1， 否则返回0
int StackEmpty(Stack* S)
{
	if (S->top == S->base)
	{
		return 1;
	}
	return 0;
}

size_t Stacksize(Stack * S)
{
	return (S->top) - (S->base);
}

void StackPop(Stack * S)
{
	if (!StackEmpty(S))
	{
		S->top--;
	}
}

void StackPush(Stack * S, Datatype x)
{
	if ((S->top) - (S->base) == S->capcity - 1)
	{
		S->capcity *= 2;
		S->_array = (Datatype *)realloc(S->_array, sizeof(Datatype) * S->capcity);
	}
	S->_array[S->top] = x;
	S->top++;
}

Datatype StackTop(Stack * S)
{
	assert(S);
	return S->_array[S->top - 1];
}