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
//从小到大
void InsretSort(int * array, size_t n)
{
	assert(array);
	for (size_t i = 1; i < n; ++i)  //[1，n)
	{
		int end = i - 1;   //[0，end]为有序区间
		int cur = array[i];
		while (end >= 0 && array[end] > cur)
		{
			array[end + 1] = array[end--];//元素后移
		}
		array[end + 1] = cur;
	}
}

//////////////////////////////////////////////////////
//从小到大
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
	for (int gap = n >> 1; gap > 0; gap >>= 1) //步长选择为n/2并对步长取半达到1
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
		for (size_t i = left; i <= right; ++i) //遍历未排序的元素  
		{
			if (array[i] < array[min])  //找到最小的元素下标
			{
				min = i;
			}
			if (array[i] > array[max])  //找最大的元素下标
			{
				max = i;
			}
		}
		if (min != left)  //最小的元素放在左边
		{
			_Swap(&array[min], &array[left]);
		}
		if (max == left) //如果最大的元素在最小元素位置，将max改为最小元素交换后的位置
		{
			max = min;
		}
		if (max != right) //将最大的元素放在右边
		{
			_Swap(&array[max], &array[right]);
		}
	}
}

///////////////////////////////////////////////////////////////
static void AdjustDown(int * array, size_t n, int root) //向下调整
{
	assert(array);
	//在阵列起始位置为0的情形中：

	//父节点i的左子节点在位置(2i+1);
	//父节点i的右子节点在位置(2i+2);
	//子节点i的父节点在位置 (i-1)/2);
	int parents = root;
	int child = parents * 2 + 1;

	while (child < (int)n)
	{
		if (child + 1 < (int)n && array[child] < array[child + 1])  //找到左右孩子大的一个
		{
			child++;
		}
		if (array[child] > array[parents]) //和父亲节点进行比较如果父亲节点小进行交换继续调整其字树
		{
			_Swap(&array[parents], &array[child]);
			parents = child;
			child = parents * 2 + 1;
		}
		else //如果其满足大堆直接跳出
		{
			break;
		}
	}
}

void HeapSort(int * array, size_t n)
{
	assert(array);

	//建堆
	for (int i = ((n - 2) >> 1); i >= 0; --i)
	{
		AdjustDown(array, n, i);
	}

	//进行排序
	int end = n - 1;
	while (end > 0)
	{
		_Swap(&array[end], &array[0]); //和最后一个进行交换
		AdjustDown(array, end, 0); //重新调整成大堆
		end--;
	}
}
/////////////////////////////////////////////////////////////////////

void BubbleSort(int * a, int n)
{
	assert(a);
	int end = n - 1;
	while (end > 0)        //控制冒泡结束的位置
	{
		int flag = 0;  //设标志
		for (int i = 0; i < end; ++i) //在区间 [0, end)
		{
			if (a[i] > a[i + 1])
			{
				_Swap(&a[i], &a[i+1]);
				flag = 1;  //如果交换标志就设为1
			}
		}
		if (flag == 0) //如果没有交换就说明有序直接结束
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

////三数取中法
//static int GetMin(int * array, int left, int right)
//{
//	assert(array);
//	int mid = left + ((right - left) >> 1);
//	if (array[mid] < array[left])
//	{
//		if (array[mid] < array[right]) //a[mid]最小
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
//		else //a[mid]为中间值
//		{
//			return mid;
//		}
//	} 
//	else  //a[mid] > a[left]
//	{
//		if (array[mid] < array[right]) //a[mid]为中间值
//		{
//			return mid;
//		}
//		else //a[mid]最大
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

//左右指针法
int PartSort1(int * array, int left, int right)
{
	assert(array);
	//使用三数取中法规避数据一边倒
	int mid = GetMin(array, left, left + ((right - left) >> 1), right);
	_Swap(&array[mid], &array[right]);   
	
	int pivot = right;//选数组最右边值为枢纽值

	while (left < right) //当左右相遇时结束交换枢纽值
	{
		//左边遇到比枢纽值小的和相等值往后走， 遇到大于枢纽值的的值停止
		while (left < right && array[left] <= array[pivot]) 
		{
			left++;
		}
		//右边遇到比枢纽值大的和相等值往后走， 遇到小于枢纽值的的值停止	
		while (left < right && array[right] >= array[pivot])
		{
			right--;
		}
		//将左右值交换 使小于枢纽值的放在左边， 大于枢纽值的放在右边
		_Swap(&array[left], &array[right]);
	}
	//找到枢纽值的位置并和枢纽值交换
	_Swap(&array[left], &array[pivot]);
	return left;
}

//挖坑法
int PartSort2(int * array, int left, int right)
{
	assert(array);
	//选数组最右边值为枢纽值,使用三数取中法规避数据一边倒
	int mid = GetMin(array, left, left + ((right - left) >> 1), right);
	_Swap(&array[mid], &array[right]);

	//第一次最右面为坑
	int pivot = array[right];
	while (left < right)
	{
		while (left < right && array[left] <= pivot)
		{
			left++;
		}
		array[right] = array[left]; //将右边坑填上后左边为坑
		while (left < right && array[right] >= pivot)
		{
			right--;
		}
		array[left] = array[right]; //将左边坑填上之后右边为坑
	}
	array[left] = pivot;//填上左右相遇点的坑
	return left;
}

//前后指针法
int PartSort3(int * array, int left, int right)
{
	assert(array);
	//选数组最右边值为枢纽值,使用三数取中法规避数据一边倒
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
		//如果小于阀值7就使用插入排序
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

	//分为[left mid] [mid + 1 right]两个区间
	_MergeSort(array, left, mid, tmp);
	_MergeSort(array, mid + 1, right, tmp);

	//至此左右区间均有序
	int left_a = left, right_a = mid;
	int left_b = mid + 1, right_b = right;
	int index = left;
	while (left_a <= right_a && left_b <= right_b)
	{
		//从小到大排序
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
			////计算需要拷贝的空间字节大小
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