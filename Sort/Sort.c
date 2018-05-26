#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"


static void _Swap(int * a, int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/////////////////////////////////////////////////////////
//从小到大
void InsretSort(int * a, size_t n)
{
	assert(a);
	for (size_t i = 0; i < n - 1; ++i)
	{
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0)
		{
			if (a[end] > tmp)
			{
				a[end + 1] = a[end];
				end--;
			}
			else
			{
				a[end + 1] = tmp;
				break;
			}
		}
		if (end == -1)
		{
			a[end + 1] = tmp;
		}
	}
}


//////////////////////////////////////////////////////
//从小到大
void ShallSort(int * a, size_t n)
{
	assert(a);
	for(int gap = n / 2 + 1; gap > 0; gap /= 2)
	{
		for (size_t i = 0; i < n - gap; i++)
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				if (a[end] > tmp)
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
				{
					a[end + gap] = tmp;
					break;
				}
			}
			if (end < 0)
			{
				a[end + gap] = tmp;
			}
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
void SelectSort(int * a, size_t n)
{
	assert(a);
	int min = 0, max = 0;
	for (size_t left = 0, right = n - 1; left < right; left++, right--)
	{
		min = left;
		max = right;
		for (size_t i = left; i <= right; ++i)
		{
			if (a[i] < a[min])
			{
				min = i;
			}
			if (a[i] > a[max])
			{
				max = i;
			}
		}
		if (min != left)
		{
			_Swap(&a[min], &a[left]);
		}
		if (max != right && !(min == right && max == left))
		{
			_Swap(&a[max], &a[right]);
		}
	}
}

///////////////////////////////////////////////////////////////
static void AdjustDown(int * a, size_t n, int root)
{
	assert(a);
	int parents = root;
	int child = parents * 2 + 1;
	while (child < (int)n)
	{
		if (child + 1 < (int)n && a[child] < a[child + 1])
		{
			child++;
		}
		if (a[child] > a[parents])
		{
			_Swap(&a[parents], &a[child]);
			parents = child;
			child = parents * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void HeapSort(int * a, size_t n)
{
	assert(a);
	for (int i = ((n - 2) >> 1); i >= 0; --i)
	{
		AdjustDown(a, n, i);
	}
	int end = n - 1;
	while (end > 0)
	{
		_Swap(&a[end], &a[0]);
		AdjustDown(a, end, 0);
		end--;
	}
}

/////////////////////////////////////////////////////////////////////
static int GetMin(int * a, int left, int right)
{
	assert(a);
	int mid = left + ((right - left) >> 1);
	if (a[mid] < a[left])
	{
		if (a[mid] < a[right]) //a[mid]最小
		{
			if (a[right] > a[left])
			{
				return left;
			}
			else
			{
				return right;
			}
		}
		else //a[mid]为中间值
		{
			return mid;
		}
	} 
	else  //a[mid] > a[left]
	{
		if (a[mid] < a[right]) //a[mid]为中间值
		{
			return mid;
		}
		else //a[mid]最大
		{
			if (a[left] > a[right])
			{
				return right;
			}
			else
			{
				return left;
			}
		}
	}
}

//左右指针法
int PartSort1(int * a, int left, int right)
{
	assert(a);
	//使用三数取中法规避数据一边倒
	int min = GetMin(a, left, right);
	_Swap(&a[min], &a[right]);   
	
	int cmp = right;//选数组最右边值为枢纽值

	while (left < right) //当左右相遇时结束交换枢纽值
	{
		//左边遇到比枢纽值小的和相等值往后走， 遇到大于枢纽值的的值停止
		while (left < right && a[left] <= a[cmp]) 
		{
			left++;
		}
		//右边遇到比枢纽值大的和相等值往后走， 遇到小于枢纽值的的值停止	
		while (left < right && a[right] >= a[cmp])
		{
			right--;
		}
		//将左右值交换 使小于枢纽值的放在左边， 大于枢纽值的放在右边
		_Swap(&a[left], &a[right]);
	}
	//找到枢纽值的位置并和枢纽值交换
	_Swap(&a[left], &a[cmp]);
	return left;
}

//挖坑法
int PartSort2(int * a, int left, int right)
{
	assert(a);
	assert(a);
	//选数组最右边值为枢纽值,使用三数取中法规避数据一边倒
	int min = GetMin(a, left, right);
	_Swap(&a[min], &a[right]);

	//第一次最右面为坑
	int cmp = a[right];
	while (left < right)
	{
		while (left < right && a[left] <= cmp)
		{
			left++;
		}
		a[right] = a[left]; //将右边坑填上后左边为坑
		while (left < right && a[right] >= cmp)
		{
			right--;
		}
		a[left] = a[right]; //将左边坑填上之后右边为坑
	}
	a[left] = cmp;//填上左右相遇点的坑
	return left;
}

//前后指针法
int PartSort3(int * a, int left, int right)
{
	assert(a);
	int prev = left - 1, cur = left;
	while (cur < right)
	{
		if (a[cur] <= a[right] && ++prev != cur )
		{
			_Swap(&a[prev], &a[cur]);
		}
		cur++;
	}
	_Swap(&a[right], &a[++prev]);
	return prev;
}


void QuickSort(int * a, int left, int right)
{
	assert(a);
	if (left >= right)
	{
		return;
	}
	int div = PartSort1(a, left, right);
	QuickSort(a, left, div - 1);
	QuickSort(a, div + 1, right);
}

void QuickSortNR(int * a, int left, int right)
{
	assert(a);
	Stack S;
	StackInit(&S, 10);

	//先入左然后入右即取出时相反
	StackPush(&S, left);
	StackPush(&S, right);

	while (!StackEmpty(&S))	
	{
		//出栈时先出右再出左
		int _right = StackTop(&S);
		StackPop(&S);
		int _left = StackTop(&S);
		StackPop(&S);

		int div = PartSort1(a, _left, _right);

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

void _MergeSort(int * a, int left, int right, int * tmp)
{
	assert(a);
	if (left >= right)
	{
		return;
	}
	int mid = left + ((right - left) >> 1);

	//分为[left mid] [mid + 1 right]两个区间
	_MergeSort(a, left, mid, tmp);
	_MergeSort(a, mid + 1, right, tmp);

	//至此左右区间均有序
	int left_a = left, right_a = mid;
	int left_b = mid + 1, right_b = right;
	int index = left;
	while (left_a <= right_a && left_b <= right_b)
	{
		//从小到大排序
		if (a[left_a] > a[left_b])
		{
			tmp[index++] = a[left_b++];
		}
		else
		{
			tmp[index++] = a[left_a++];
		}
	}
	while (left_a <= right_a)
	{
		tmp[index++] = a[left_a++];
	}
	while (left_b <= right_b)
	{
		tmp[index++] = a[left_b++];
	}
	memcpy(&a[left], &tmp[left], sizeof(int)* (right - left + 1));
}

void MergeSort(int * a, int left, int right)
{
	assert(a);
	int * tmp = (int *)malloc(sizeof(int) * (right - left + 1));
	_MergeSort(a, left, right, tmp);
	free(tmp);
}

void MergeSortNR(int * a, int left, int right)
{
	assert(a);
	int * tmp = (int *)malloc(sizeof(int) * (right - left + 1));

	for(int gap = 1; gap <= (right - left + 1); gap <<= 1)
	{
		int cur = left;
		while (cur <= right)
		{
			//计算区间中点分为两个区间 [cur mid - 1] [mid mid + gap - 1]
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
				//从小到大排序
				if (a[left_a] > a[left_b])
				{
					tmp[index++] = a[left_b++];
				}
				else
				{
					tmp[index++] = a[left_a++];
				}
			}

			while (left_a <= right_a)
			{
				tmp[index++] = a[left_a++];
			}
			while (left_b <= right_b)
			{
				tmp[index++] = a[left_b++];
			}
			int count_bit = (gap << 1) > (right - left + 1) ? (right - left + 1) : (gap << 1);
			memcpy(&a[cur], &tmp[cur], sizeof(int)* count_bit);
			cur += (gap << 1);
		}//while(cur <= right)
	}
	free(tmp);
}


////////////////////////////////////////////////////////////////////
void TestMergeSort()
{
	//int a[] = { 2, 5, 8, 4, 3, 1, 9, 6 };
	int a[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	MergeSortNR(a, 0, sizeof(a) / sizeof(int) - 1);
	//MergeSort(a, 0, sizeof(a) / sizeof(int)- 1);
	for (size_t i = 0; i < sizeof(a) / sizeof(int); ++i)
	{
		printf("%d ", a[i]);
	}
}

void TestHeapSort()
{
	int a[] = { 2, 5, 8, 4, 3, 1, 9, 6 };
	//int a[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	HeapSort(a, sizeof(a) / sizeof(int));
	for (size_t i = 0; i < sizeof(a) / sizeof(int); ++i)
	{
		printf("%d ", a[i]);
	}
}

void TestQuickSort()
{
	//int a[] = { 2, 5, 8, 4, 3, 1, 9, 6 };
	int a[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	//QuickSort(a, 0,  sizeof(a) / sizeof(int) - 1);
	QuickSortNR(a, 0,  sizeof(a) / sizeof(int) - 1);

	for (size_t i = 0; i < sizeof(a) / sizeof(int); ++i)
	{
		printf("%d ", a[i]);
	}
}

void TestSelectSort()
{
	//int a[] = { 2, 5, 8, 4, 3, 1, 9, 6 };
	int a[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	SelectSort(a, sizeof(a) / sizeof(int));
	for (size_t i = 0; i < sizeof(a) / sizeof(int); ++i)
	{
		printf("%d ", a[i]);
	}
}

void TestShallSort()
{
	//int a[] = { 2, 5, 8, 4, 3, 1, 9, 6 };
	int a[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	ShallSort(a, sizeof(a) / sizeof(int));
	for (size_t i = 0; i < sizeof(a) / sizeof(int); ++i)
	{
		printf("%d ", a[i]);
	}
}
void TestInsretSort()
{
	int a[] = { 2, 5, 8, 4, 3, 1, 9, 6 };
	InsretSort(a, sizeof(a) / sizeof(int));
	for (size_t i = 0; i < sizeof(a) / sizeof(int); ++i)
	{
		printf("%d ", a[i]);
	}
}

int main()
{
	//TestInsretSort();
	//TestShallSort();
	//TestSelectSort();
	//TestHeapSort();
	//TestQuickSort();
	TestMergeSort();
	system("pause");
	return 0;
}