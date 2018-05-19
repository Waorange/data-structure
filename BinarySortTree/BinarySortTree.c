#include "BInarySortTree.h"
#include "stack.h"
#include <assert.h>
#include <string.h>


//��������ʼ���ڵ�
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


//�Ƚϼ�ֵ��С
static int _campare(KeyType cur_key, KeyType key)
{
	return cur_key > key ? 1 : -1;
	//return strcmp(cur_key, key);
}


void BSTreeInsert(BSTreeNode ** root, KeyType key, ValueType value)
{
	assert(root);
	//������ֵ�ϴ�����������ֵ��С�����ң�һֱ��ĩ�˼������
	
	//���ͷ���Ϊ��ֱ�Ӳ���
	if (*root == NULL)
	{
		*root = _BuyBSTreeNode(key, value);
		return;
	}

	//��ֵ��ֱͬ�ӷ���
	if (BSTreeFind(*root, key) != NULL)
	{
		return;
	}

	//��ʼ������Ľڵ�
	BSTreeNode * Node = _BuyBSTreeNode(key, value);

	BSTreeNode * cur = *root;
	BSTreeNode * parents = NULL;
	int _cmp = 0;
	//Ѱ�Ҳ���λ�õĸ��׽ڵ�
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
	//������ֵ������� ������ֵС������ 
	//��ֵ��ͬ�ҵ��˷��ص�ǰ�ڵ� ���ؿձ�ʾû�ҵ�
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
		else//�ҵ���Ҫɾ���Ľڵ�
		{
			//���Һ��Ӷ���Ϊ�յĽڵ��Ƚ�Ҫɾ���Ľڵ��滻����������(������)�ļ�ֵ���(��С)�Ľڵ�λ��
			//�����������
			if (cur->lchild != NULL && cur->rchild != NULL)
			{
				BSTreeNode * left_max = cur->lchild;
				parents = cur;

				//����������ֵ���ڵ�
				while (left_max->rchild)
				{
					parents = left_max;
					left_max = left_max->rchild;
				}
				cur->_key = left_max->_key;
				cur->_value = left_max->_value;
			}

			//ɾ���ڵ�
			
			if (cur->lchild != NULL) //��Ϊ��
			{
				//��Ҫɾ���Ľڵ����������˫��Ȼ���ͷ�Ҫɾ���Ľڵ�
				if (parents == NULL) //ɾ���Ľڵ�Ϊͷ�ڵ�
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
			else  //��Ϊ��
			{
				if (parents == NULL) //ɾ���Ľڵ�Ϊͷ�ڵ�
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
