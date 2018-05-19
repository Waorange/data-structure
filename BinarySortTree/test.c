#include "BInarySortTree.h"
#include <stdlib.h>
#include <stdio.h>

//void test()
//{
//	BSTreeNode *tree = NULL;
//	BSTreeInsert(&tree, "tree", "Ê÷");
//	BSTreeInsert(&tree, "sort", "ÅÅÐò");
//	BSTreeInsert(&tree, "binary", "¶þ·Ö");
//	BSTreeInsert(&tree, "return", "·µ»Ø");
//	BSTreeInsert(&tree, "hash", "¹þÏ£");
//	BSTreeInsert(&tree, "list", "Á´±í");
//	BSTreeInOrder(tree);
//
//	printf("%s\n", BSTreeFind(tree, "tree")->_value);
//	printf("%s\n", BSTreeFind(tree, "return")->_value);
//	printf("%s\n", BSTreeFind(tree, "hash")->_value);
//	printf("%s\n", BSTreeFind(tree, "list")->_value);
//
//	BSTreeRemove(&tree, "tree");
//	BSTreeRemove(&tree, "sort");
//	BSTreeRemove(&tree, "binary");
//	BSTreeRemove(&tree, "return");
//	BSTreeRemove(&tree, "list");
//	BSTreeInOrder(tree);
//
//	BSTreeDestory(&tree);
//}

void test2()
{
	int a[] = {5,3,4,1,7,8,2,6,0,9}; 
	BSTreeNode* tree = NULL; 
	 
	for (int i = 0; i < sizeof(a)/sizeof(a[0]); ++i) 
	{ 
		BSTreeInsert(&tree, a[i], "1"); 
	} 
	BSTreeInOrder(tree);
}

int main()
{
	//test();
	test2();
	system("pause");
	return 0;
}