#ifndef _BINARYSORTTREE_H_
#define _BINARYSORTTREE_H_

typedef int KeyType;
typedef char* ValueType;

typedef struct BSTreeNode {
	struct BSTreeNode * lchild;
	struct BSTreeNode * rchild;
	KeyType _key;
	ValueType _value;
}BSTreeNode;

void BSTreeInsert(BSTreeNode ** root, KeyType key, ValueType value);
void BSTreeRemove(BSTreeNode ** root, KeyType key);
BSTreeNode * BSTreeFind(BSTreeNode * root, KeyType key);
void BSTreeDestory(BSTreeNode ** root);
void BSTreeInOrder(BSTreeNode * root);

#endif
