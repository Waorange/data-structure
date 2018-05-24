#include "binarytree.h"


BTree * BTreeBuild(BDatatype * arr, size_t * indix, BDatatype flag)
{
	if (arr[*indix] == flag)
	{
		(*indix)++;
		return NULL;
	}
	BTree * Node = (BTree *)malloc(sizeof(BTree));
	assert(Node);
	Node->_data = arr[(*indix)++];
	Node->lchild = BTreeBuild(arr, indix, flag);
	Node->rchild = BTreeBuild(arr, indix, flag);
	return Node;
}
void BTreePrevOrder(BTree * root)
{
	if (root == NULL)
	{
		return;
	}
	printf("%d ", root->_data);
	BTreePrevOrder(root->lchild);
	BTreePrevOrder(root->rchild);
}
void BTreeInOrder(BTree * root)
{
	if (root == NULL)
	{
		return;
	}
	BTreeInOrder(root->lchild);
	printf("%d ", root->_data);
	BTreeInOrder(root->rchild);
}
void BTreeLastOrder(BTree * root)
{
	if (root == NULL)
	{
		return;
	}
	BTreeLastOrder(root->lchild);
	BTreeLastOrder(root->rchild);
	printf("%d ", root->_data);
}
void BTreeLevelOrder(BTree * root)
{
	assert(root);
	Queue Q;
	QueueInit(&Q);
	QueuePush(&Q, root);
	while (!QueueEmpty(&Q))
	{
		BTree * cur = QueueFront(&Q);
		QueuePop(&Q);
		printf("%d ", cur->_data);
		if (cur->lchild != NULL)
		{
			QueuePush(&Q, cur->lchild);
		}
		if (cur->rchild != NULL)
		{
			QueuePush(&Q, cur->rchild);
		}

	}
}

size_t BTreeSize(BTree * root)
{
	if (root == NULL)
	{
		return 0;
	}

	return BTreeSize(root->lchild) + BTreeSize(root->rchild) + 1;
}
size_t BTreeleafSize(BTree * root)
{
	if (root == NULL)
	{
		return 0;
	}
	if (root->lchild == NULL && root->rchild == NULL)
	{
		return 1;
	}
	return BTreeleafSize(root->lchild) + BTreeleafSize(root->rchild);
}
size_t BTreeKLevelSize(BTree * root, size_t k)
{
	if (root == NULL)
	{
		return 0;
	}
	if (k == 1)
	{
		return 1;
	}
	return BTreeKLevelSize(root->lchild, k - 1) + BTreeKLevelSize(root->rchild, k - 1);
}
size_t BTreeDeep(BTree * root)
{
	if (root == NULL)
	{
		return 0;
	}
	int nlift = (int)BTreeDeep(root->lchild);
	int nright = (int)BTreeDeep(root->rchild);
	return nlift > nright ? nlift + 1 : nright + 1;
}

void BTreePrevOrderNonR(BTree* root)
{
	Stack S;
	StackInit(&S, 10);
	BTree * cur = root;
	while (cur != NULL || !StackEmpty(&S))
	{
		while (cur != NULL)
		{
			printf("%d ", cur->_data);
			StackPush(&S, cur);
			cur = cur->lchild;
		}
		BTree* Top = StackTop(&S);
		StackPop(&S);
		cur = Top->rchild;
	}
}
void BTreeInOrderNonR(BTree* root)
{
	Stack S;
	StackInit(&S, 10);
	BTree * cur = root;
	while (cur != NULL || !StackEmpty(&S))
	{
		while (cur != NULL)
		{
			StackPush(&S, cur);
			cur = cur->lchild;
		}
		BTree* Top = StackTop(&S);
		printf("%d ", Top->_data);
		StackPop(&S);
		cur = Top->rchild;
	}
}
void BTreePostOrderNonR(BTree* root)
{
	Stack S;
	StackInit(&S, 10);
	BTree * cur = root, *last = NULL;
	while (cur != NULL || !StackEmpty(&S))
	{
		while (cur != NULL)
		{
			StackPush(&S, cur);
			cur = cur->lchild;
		}
		BTree* Top = StackTop(&S);
		if (Top->rchild == NULL || Top->rchild == last)
		{
			printf("%d ", Top->_data);
			StackPop(&S);
			last = Top;
		}
		else
		{
			cur = Top->rchild;
		}
	}
}

void test()
{
	BDatatype arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6,'#' ,'#' ,'#' };
	size_t indix = 0;
	BTree * root = BTreeBuild(arr, &indix, 35);
	BTreePrevOrder(root);
	printf("\n");
	BTreeInOrder(root);
	printf("\n");
	BTreeLastOrder(root);
	printf("\n");
	printf("BTreeSize: %d\n", (int)BTreeSize(root)); 
	printf("leafSize: %d\n", (int)BTreeleafSize(root));
	printf("KlevelSize: %d\n", (int)BTreeKLevelSize(root, 1));
	printf("Deep: %d\n", (int)BTreeDeep(root));
	BTreePrevOrderNonR(root);
	printf("\n");
	BTreeInOrderNonR(root);
	printf("\n");
	BTreePostOrderNonR(root);
	printf("\n");
	BTreeLevelOrder(root);
	printf("\n")
}

int main()
{
	test();
	return 0;
}