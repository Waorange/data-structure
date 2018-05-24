#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>
#include <stdlib.h>
typedef struct BinaryNode* SDatatype;

typedef struct stack {
	SDatatype* _array;
	size_t top;
	size_t base;
	int capcity;
}Stack;

void StackInit(Stack * S, int x);
int StackEmpty(Stack* S);
size_t Stacksize(Stack * S);
void StackPop(Stack * S);
void StackPush(Stack * S, SDatatype x);
SDatatype StackTop(Stack * S);

#endif // !_STACK_H_

