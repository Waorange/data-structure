#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include <time.h>

#define N 1000000


static void _Swap(int * a, int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/////////////////////////////////////////////////////////
//��С����
void InsretSort(int * array, size_t n)
{
	assert(array);
	for (size_t i = 1; i < n; ++i)  //[1��n)
	{
		int end = i - 1;   //[0��end]Ϊ��������
		int cur = array[i];
		while (end >= 0 && array[end] > cur)
		{
			array[end + 1] = array[end--];//Ԫ�غ���
		}
		array[end + 1] = cur;
	}
}

//////////////////////////////////////////////////////
//��С����
//void ShallSort(int * array, size_t n)
//{
//	assert(array);
//	for(int gap = n / 2 + 1; gap > 0; gap /= 2)
//	{
//		for (size_t i = 0; i < n - gap; i++)
//		{
//			int end = i;
//			int tmp = array[end + gap];
//			while (end >= 0)
//			{
//				if (array[end] > tmp)
//				{
//					array[end + gap] = array[end];
//					end -= gap;
//				}
//				else
//				{
//					array[end + gap] = tmp;
//					break;
//				}
//			}
//			if (end < 0)
//			{
//				array[end + gap] = tmp;
//			}
//		}
//	}
//}

void ShallSort(int * array, size_t n)
{
	assert(array);
	for (int gap = n >> 1; gap > 0; gap >>= 1) //����ѡ��Ϊn/2���Բ���ȡ��ﵽ1
	{
		for (size_t i = gap; i < n; i++)
		{
			int end = i - gap;
			int cur = array[i];
			while (end >= 0 && array[end] > cur)
			{
				array[end + gap] = array[end];
				end -= gap;
			}
			array[end + gap] = cur;
		}
	}//gap
}


/////////////////////////////////////////////////////////////////////////////
void SelectSort(int * array, size_t n)
{
	assert(array);
	int min = 0, max = 0;

	for (size_t left = 0, right = n - 1; left < right; left++, right--)
	{
		min = left;
		max = right;
		for (size_t i = left; i <= right; ++i) //����δ�����Ԫ��  
		{
			if (array[i] < array[min])  //�ҵ���С��Ԫ���±�
			{
				min = i;
			}
			if (array[i] > array[max])  //������Ԫ���±�
			{
				max = i;
			}
		}
		if (min != left)  //��С��Ԫ�ط������
		{
			_Swap(&array[min], &array[left]);
		}
		if (max == left) //�������Ԫ������СԪ��λ�ã���max��Ϊ��СԪ�ؽ������λ��
		{
			max = min;
		}
		if (max != right) //������Ԫ�ط����ұ�
		{
			_Swap(&array[max], &array[right]);
		}
	}
}

///////////////////////////////////////////////////////////////
static void AdjustDown(int * array, size_t n, int root) //���µ���
{
	assert(array);
	//��������ʼλ��Ϊ0�������У�

	//���ڵ�i�����ӽڵ���λ��(2i+1);
	//���ڵ�i�����ӽڵ���λ��(2i+2);
	//�ӽڵ�i�ĸ��ڵ���λ�� (i-1)/2);
	int parents = root;
	int child = parents * 2 + 1;

	while (child < (int)n)
	{
		if (child + 1 < (int)n && array[child] < array[child + 1])  //�ҵ����Һ��Ӵ��һ��
		{
			child++;
		}
		if (array[child] > array[parents]) //�͸��׽ڵ���бȽ�������׽ڵ�С���н�����������������
		{
			_Swap(&array[parents], &array[child]);
			parents = child;
			child = parents * 2 + 1;
		}
		else //�����������ֱ������
		{
			break;
		}
	}
}

void HeapSort(int * array, size_t n)
{
	assert(array);

	//����
	for (int i = ((n - 2) >> 1); i >= 0; --i)
	{
		AdjustDown(array, n, i);
	}

	//��������
	int end = n - 1;
	while (end > 0)
	{
		_Swap(&array[end], &array[0]); //�����һ�����н���
		AdjustDown(array, end, 0); //���µ����ɴ��
		end--;
	}
}
/////////////////////////////////////////////////////////////////////

void BubbleSort(int * a, int n)
{
	assert(a);
	int end = n - 1;
	while (end > 0)        //����ð�ݽ�����λ��
	{
		int flag = 0;  //���־
		for (int i = 0; i < end; ++i) //������ [0, end)
		{
			if (a[i] > a[i + 1])
			{
				_Swap(&a[i], &a[i+1]);
				flag = 1;  //���������־����Ϊ1
			}
		}
		if (flag == 0) //���û�н�����˵������ֱ�ӽ���
		{
			break;
		}
		end--;
	}
}

/////////////////////////////////////////////////////////////////////

int GetMin(int x[], int a, int b, int c)
{
	return x[a] < x[b] ? (x[b] < x[c] ? b : x[a] < x[c] ? c : a)
		: x[b] > x[c] ? b : x[a] > x[c] ? c : a;
}

////����ȡ�з�
//static int GetMin(int * array, int left, int right)
//{
//	assert(array);
//	int mid = left + ((right - left) >> 1);
//	if (array[mid] < array[left])
//	{
//		if (array[mid] < array[right]) //a[mid]��С
//		{
//			if (array[right] > array[left])
//			{
//				return left;
//			}
//			else
//			{
//				return right;
//			}
//		}
//		else //a[mid]Ϊ�м�ֵ
//		{
//			return mid;
//		}
//	} 
//	else  //a[mid] > a[left]
//	{
//		if (array[mid] < array[right]) //a[mid]Ϊ�м�ֵ
//		{
//			return mid;
//		}
//		else //a[mid]���
//		{
//			if (array[left] > array[right])
//			{
//				return right;
//			}
//			else
//			{
//				return left;
//			}
//		}
//	}
//}

//����ָ�뷨
int PartSort1(int * array, int left, int right)
{
	assert(array);
	//ʹ������ȡ�з��������һ�ߵ�
	int mid = GetMin(array, left, left + ((right - left) >> 1), right);
	_Swap(&array[mid], &array[right]);   
	
	int pivot = right;//ѡ�������ұ�ֵΪ��Ŧֵ

	while (left < right) //����������ʱ����������Ŧֵ
	{
		//�����������ŦֵС�ĺ����ֵ�����ߣ� ����������Ŧֵ�ĵ�ֵֹͣ
		while (left < right && array[left] <= array[pivot]) 
		{
			left++;
		}
		//�ұ���������Ŧֵ��ĺ����ֵ�����ߣ� ����С����Ŧֵ�ĵ�ֵֹͣ	
		while (left < right && array[right] >= array[pivot])
		{
			right--;
		}
		//������ֵ���� ʹС����Ŧֵ�ķ�����ߣ� ������Ŧֵ�ķ����ұ�
		_Swap(&array[left], &array[right]);
	}
	//�ҵ���Ŧֵ��λ�ò�����Ŧֵ����
	_Swap(&array[left], &array[pivot]);
	return left;
}

//�ڿӷ�
int PartSort2(int * array, int left, int right)
{
	assert(array);
	//ѡ�������ұ�ֵΪ��Ŧֵ,ʹ������ȡ�з��������һ�ߵ�
	int mid = GetMin(array, left, left + ((right - left) >> 1), right);
	_Swap(&array[mid], &array[right]);

	//��һ��������Ϊ��
	int pivot = array[right];
	while (left < right)
	{
		while (left < right && array[left] <= pivot)
		{
			left++;
		}
		array[right] = array[left]; //���ұ߿����Ϻ����Ϊ��
		while (left < right && array[right] >= pivot)
		{
			right--;
		}
		array[left] = array[right]; //����߿�����֮���ұ�Ϊ��
	}
	array[left] = pivot;//��������������Ŀ�
	return left;
}

//ǰ��ָ�뷨
int PartSort3(int * array, int left, int right)
{
	assert(array);
	//ѡ�������ұ�ֵΪ��Ŧֵ,ʹ������ȡ�з��������һ�ߵ�
	int mid = GetMin(array, left, left + ((right - left) >> 1), right);
	_Swap(&array[mid], &array[right]);

	int prev = left - 1, cur = left;
	while (cur < right)
	{
		if (array[cur] <= array[right] && ++prev != cur )
		{
			_Swap(&array[prev], &array[cur]);
		}
		cur++;
	}
	_Swap(&array[right], &array[++prev]);
	return prev;
}


void QuickSort(int * array, int left, int right)
{
	assert(array);
	if (left >= right)
	{
		return;
	}

	if (right - left + 1 == 7)
	{
		InsretSort(array, right - left + 1);
		return;
	}
	int div = PartSort3(array, left, right);

	QuickSort(array, left, div - 1);
	QuickSort(array, div + 1, right);
}

void QuickSortNR(int * array, int left, int right)
{
	assert(array);
	Stack S;
	StackInit(&S, 10);

	//������Ȼ�����Ҽ�ȡ��ʱ�෴
	StackPush(&S, left);
	StackPush(&S, right);

	while (!StackEmpty(&S))	
	{
		//��ջʱ�ȳ����ٳ���
		int _right = StackTop(&S);
		StackPop(&S);
		int _left = StackTop(&S);
		StackPop(&S);
		//���С�ڷ�ֵ7��ʹ�ò�������
		if (right - left + 1 == 7)
		{
			InsretSort(array, right - left + 1);
			continue;
		}
		int div = PartSort1(array, _left, _right);

		if (_left < div - 1)
		{
			StackPush(&S, _left);
			StackPush(&S, div - 1);
		}
		if (div + 1 < _right)
		{
			StackPush(&S, div + 1);
			StackPush(&S, _right);
		}
	}
}

////////////////////////////////////////////////////////////////////

void _MergeSort(int * array, int left, int right, int * tmp)
{
	assert(array);
	if (left >= right)
	{
		return;
	}
	int mid = left + ((right - left) >> 1);

	//��Ϊ[left mid] [mid + 1 right]��������
	_MergeSort(array, left, mid, tmp);
	_MergeSort(array, mid + 1, right, tmp);

	//�����������������
	int left_a = left, right_a = mid;
	int left_b = mid + 1, right_b = right;
	int index = left;
	while (left_a <= right_a && left_b <= right_b)
	{
		//��С��������
		if (array[left_a] > array[left_b])
		{
			tmp[index++] = array[left_b++];
		}
		else
		{
			tmp[index++] = array[left_a++];
		}
	}
	while (left_a <= right_a)
	{
		tmp[index++] = array[left_a++];
	}
	while (left_b <= right_b)
	{
		tmp[index++] = array[left_b++];
	}
	memcpy(&array[left], &tmp[left], sizeof(int)* (right - left + 1));
}

void MergeSort(int * array, int left, int right)
{
	assert(array);
	int * tmp = (int *)malloc(sizeof(int) * (right - left + 1));
	_MergeSort(array, left, right, tmp);
	free(tmp);
}


void MergeSortNR(int * array, int left, int right)
{
	assert(array);
	int * tmp = (int *)malloc(sizeof(int) * (right - left + 1));

	for (int gap = 1; gap <= (right - left + 1); gap <<= 1)
	{
		int cur = left;
		while (cur <= right)
		{
			//���������е��Ϊ�������� [cur mid - 1] [mid mid + gap - 1]
			int mid = cur + gap;

			int left_a = cur, right_a = mid - 1;
			if (right_a >= right)
			{
				break;
			}

			int left_b = mid, right_b = left_b + gap - 1;
			if (right_b > right)
			{
				right_b = right;
			}

			int index = cur;
			while (left_a <= right_a && left_b <= right_b)
			{
				//��С��������
				if (array[left_a] > array[left_b])
				{
					tmp[index++] = array[left_b++];
				}
				else
				{
					tmp[index++] = array[left_a++];
				}
			}

			while (left_a <= right_a)
			{
				tmp[index++] = array[left_a++];
			}
			while (left_b <= right_b)
			{
				tmp[index++] = array[left_b++];
			}
			////������Ҫ�����Ŀռ��ֽڴ�С
			int count_byte = (right_b - cur + 1) < (gap << 1) ? (right_b - cur + 1) : (gap << 1);
			memcpy(&array[cur], &tmp[cur], sizeof(int)* count_byte);

			cur += (gap << 1);
		}//while(cur <= right)
	}
	free(tmp);
}


////////////////////////////////////////////////////////////////////



void TestSort()
{
	//int a[] = { 2, 5, 8, 4, 3, 1, 9, 6 };
	//int a[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	int * a;
	a = (int *)malloc(sizeof(int) * N);
	for (int i = 0; i < N; ++i)
	{
		a[i] = rand();
	}
	//InsretSort(a, N);
	//ShallSort(a, N);

	//SelectSort(a, N);
	//HeapSort(a, N);

	//BubbleSort(a, N);
	//QuickSort(a, 0, N - 1);
	//QuickSortNR(a, 0, N - 1);

	//MergeSort(a, 0, N - 1);
	MergeSortNR(a, 0, N - 1);

	for (size_t i = 0; i < N; ++i)
	{
		printf("%d ", a[i]);
	}
}

int main()
{
	srand((unsigned int)time(NULL));
	TestSort();
	system("pause");
	return 0;
}