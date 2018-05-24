#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int BDatatype;

typedef struct BinaryNode{
	BDatatype _data;
	struct BinaryNode *lchild;
	struct BinaryNode *rchild;
}BTree;

#include "stack.h"
#include "Queue.h"

BTree * BTreeBuild(BDatatype * arr, size_t * indix, BDatatype flag);
void BTreePrevOrder(BTree * root);
void BTreeInOrder(BTree * root);
void BTreeLastOrder(BTree * root);
void BTreeLevelOrder(BTree * root);

size_t BTreeSize(BTree * root);
size_t BTreeleafSize(BTree * root);
size_t BTreeKLevelSize(BTree * root, size_t k);
size_t BTreeDeep(BTree * root);

void BTreePrevOrderNonR(BTree* root);
void BTreeInOrderNonR(BTree* root);
void BTreePostOrderNonR(BTree* root);



#endif
