#include "BitMap.h"

void BitMapInit(BitMap * bm, size_t range)
{
	assert(bm);
	bm->_bits = (size_t *)malloc(sizeof(size_t) * ((range >> 5) + 1));
	assert(bm->_bits);
	memset(bm->_bits, 0, sizeof(size_t) * ((range >> 5) + 1));
	bm->_range = range;
}

void BitMapSet(BitMap * bm, size_t x)
{
	assert(bm);
	int index = x >> 5;
	int num = x % 32;
	bm->_bits[index] |= (1 << num);
}
void BitMapReset(BitMap * bm, size_t x)
{
	assert(bm);
	int index = x >> 5;
	int num = x % 32;
	bm->_bits[index] &= ~(1 << num);
}
void BitMapDestory(BitMap * bm)
{
	free(bm->_bits);
	bm->_range = 0;
}

//返回0表示不存在 返回1表示存在
int BitMapFind(BitMap * bm, size_t x)
{
	assert(bm);
	int index = x >> 5;
	int num = x % 32;
	return bm->_bits[index] >> num & 1;
}

void test()
{
	BitMap bm;
	BitMapInit(&bm, 10000);

	BitMapSet(&bm, 1000);
	BitMapSet(&bm, 1002);
	BitMapSet(&bm, 1004);
	BitMapSet(&bm, 1006);
	BitMapSet(&bm, 1008);
	BitMapSet(&bm, 1010);
	BitMapSet(&bm, 1012);
	BitMapSet(&bm, 1014);
	BitMapSet(&bm, 1016);
	BitMapSet(&bm, 1018);

	for (int i = 1000; i < 1020; i++)
	{
		printf("%d:%d\n", i , BitMapFind(&bm, i));
	}

	BitMapReset(&bm, 1002);
	BitMapReset(&bm, 1004);
	BitMapReset(&bm, 1006);
	BitMapReset(&bm, 1008);
	printf("删除1002 1004 1006 1008之后\n");
	for (int i = 1000; i < 1020; i++)
	{
		printf("%d:%d\n", i, BitMapFind(&bm, i));
	}
}

int main()
{
	test();
	system("pause");
	return 0;
}