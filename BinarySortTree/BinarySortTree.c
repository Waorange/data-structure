#include "BInarySortTree.h"
#include "stack.h"
#include <assert.h>
#include <string.h>


//建立并初始化节点
static BSTreeNode * _BuyBSTreeNode(KeyType key, ValueType value)
{
	BSTreeNode * node = (BSTreeNode *)malloc(sizeof(BSTreeNode));
	assert(node);
	node->_key = key;
	node->_value = value;
	node->lchild = NULL;
	node->rchild = NULL;
	return node;
}


//比较键值大小
static int _campare(KeyType cur_key, KeyType key)
{
	return cur_key > key ? 1 : -1;
	//return strcmp(cur_key, key);
}


void BSTreeInsert(BSTreeNode ** root, KeyType key, ValueType value)
{
	assert(root);
	//遇到键值较大向左，遇到键值较小者向右，一直到末端即插入点
	
	//如果头结点为空直接插入
	if (*root == NULL)
	{
		*root = _BuyBSTreeNode(key, value);
		return;
	}

	//键值相同直接返回
	if (BSTreeFind(*root, key) != NULL)
	{
		return;
	}

	//初始化插入的节点
	BSTreeNode * Node = _BuyBSTreeNode(key, value);

	BSTreeNode * cur = *root;
	BSTreeNode * parents = NULL;
	int _cmp = 0;
	//寻找插入位置的父亲节点
	while (cur)
	{
		parents = cur;
		_cmp = _campare(cur->_key, key);
		cur = _cmp > 0 ? cur->lchild : cur->rchild;
	}
	if (_cmp > 0)
	{
		parents->lchild = Node;
	}
	else
	{
		parents->rchild = Node;
	}
}

void BSTreeInOrder(BSTreeNode * root)
{
	Stack S;
	StackInit(&S, 10);
	BSTreeNode * cur = root;
	while (cur || !StackEmpty(&S))
	{
		while (cur)
		{
			StackPush(&S, cur);
			cur = cur->lchild;
		}
		BSTreeNode * _top = StackTop(&S);
		StackPop(&S);
		printf("[%d: %s]\n", _top->_key, _top->_value);
		cur = _top->rchild;
	}
}


BSTreeNode * BSTreeFind(BSTreeNode * root, KeyType key)
{
	//遇到键值大的向左， 遇到键值小的向右 
	//键值相同找到了返回当前节点 返回空表示没找到
	BSTreeNode * cur = root;
	while (cur)
	{
		int _cmp = _campare(cur->_key, key);
		if (_cmp > 0)
		{
			cur = cur->lchild;
		}
		else if (_cmp < 0)
		{
			cur = cur->rchild;
		}
		else
		{
			return cur;
		}
	}
	return NULL;
}
void BSTreeRemove(BSTreeNode ** root, KeyType key)
{
	assert(*root);
	BSTreeNode * parents = NULL;
	BSTreeNode * cur = *root;

	while (cur)
	{
		int _cmp = _campare(cur->_key, key);
		if (_cmp > 0)
		{
			parents = cur;
			cur = cur->lchild;
		}
		else if (_cmp < 0)
		{
			parents = cur;
			cur = cur->rchild;
		}
		else//找到了要删除的节点
		{
			//左右孩子都不为空的节点先将要删除的节点替换到其左子树(右子树)的键值最大(最小)的节点位置
			//换成其他情况
			if (cur->lchild != NULL && cur->rchild != NULL)
			{
				BSTreeNode * left_max = cur->lchild;
				parents = cur;

				//找左子树键值最大节点
				while (left_max->rchild)
				{
					parents = left_max;
					left_max = left_max->rchild;
				}
				cur->_key = left_max->_key;
				cur->_value = left_max->_value;
			}

			//删除节点
			
			if (cur->lchild != NULL) //右为空
			{
				//将要删除的节点的左子树给双亲然后释放要删除的节点
				if (parents == NULL) //删除的节点为头节点
				{
					*root = cur->lchild;
				}
				else if(cur == parents->lchild) 
				{
					parents->lchild = cur->lchild;
				}
				else
				{
					parents->rchild = cur->lchild;
				}
			}
			else  //左为空
			{
				if (parents == NULL) //删除的节点为头节点
				{
					*root = cur->rchild;
				}
				else if (cur == parents->lchild)
				{
					parents->lchild = cur->rchild;
				}
				else
				{
					parents->rchild = cur->rchild;
				}
			}
			free(cur);
			return;
		}

	}//whlle(cur)
}


void BSTreeDestory(BSTreeNode ** root)
{
	if (*root == NULL)
	{
		return;
	}
	BSTreeDestory(&(*root)->lchild);
	BSTreeDestory(&(*root)->rchild);
	free(*root);
}
