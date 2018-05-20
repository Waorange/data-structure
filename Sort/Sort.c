#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


static void _Swap(int * a, int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
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
	TestSelectSort();
	system("pause");
	return 0;
}