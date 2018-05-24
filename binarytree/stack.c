#include "stack.h"
#include <assert.h>

void StackInit(Stack * S, int x)
{
	S->capcity = x;
	S->_array = (SDatatype *)malloc(sizeof(SDatatype) * S->capcity);
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
	assert(S);
	return (S->top) - (S->base);
}

void StackPop(Stack * S)
{
	if (!StackEmpty(S))
	{
		S->top--;
	}
}

void StackPush(Stack * S, SDatatype x)
{
	if ((S->top) - (S->base) == S->capcity - 1)
	{
		S->capcity *= 2;
		S->_array = (SDatatype *)realloc(S->_array, sizeof(SDatatype) * S->capcity);
	}
	S->_array[S->top] = x;
	S->top++;
}

SDatatype StackTop(Stack * S)
{
	assert(S);
	return S->_array[S->top - 1];
}

