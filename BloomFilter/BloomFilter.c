#include "BloomFilter.h"

//哈希函数
/// @brief BKDR Hash Function  
/// @detail 本 算法由于在Brian Kernighan与Dennis Ritchie的《The C Programming Language》一书被展示而得名
/// 是一种简单快捷的hash算法，也是Java目前采用的字符串的Hash算法（累乘因子为31）。  
size_t _BKDRHash(KeyType str)
{
	register size_t hash = 0;
	size_t ch;
	while (ch = (size_t)*str++)
	{
		hash = hash * 131 + ch;   // 也可以乘以31、131、1313、13131、131313..           
	}
	return hash;
}
/// @brief AP Hash Function  
/// @detail 由Arash Partow发明的一种hash算法。  
size_t _APHash(KeyType str)
{
	register size_t hash = 0;
	size_t ch;
	for (long i = 0; ch = (size_t)*str++; i++)
	{
		if ((i & 1) == 0)
		{
			hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
		}
		else
		{
			hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
		}
	}
	return hash;
}
/// @brief DJB Hash Function  
/// @detail 由Daniel J. Bernstein教授发明的一种hash算法。  
size_t _DJBHash(KeyType str)
{
	size_t ch;
	register size_t hash = 5381;
	while (ch = (size_t)*str++)
	{
		hash += (hash << 5) + ch;
	}
	return hash;
}


void BloomFilterInit(BloomFilter* bf, size_t range)
{
	//误判率ε≈[1 - e^(−(nk/m))]k
	//当哈希函数个数 ε为最优解 k为3时 m 约为4.32
	//详细https://www.cnblogs.com/liyulong1982/p/6013002.html
	BitMapInit(&bf->_bm, (size_t)4.32 * range);
	bf->_hashfunc1 = &_DJBHash;
	bf->_hashfunc2 = &_BKDRHash;
	bf->_hashfunc3 = &_APHash;
}
void BloomFilterSet(BloomFilter* bf, KeyType key)
{
	assert(bf);
	size_t index1 = bf->_hashfunc1(key);
	size_t index2 = bf->_hashfunc2(key);
	size_t index3 = bf->_hashfunc3(key);
	BitMapSet(&bf->_bm, index1);
	BitMapSet(&bf->_bm, index2);
	BitMapSet(&bf->_bm, index3);
}

//返回0表示不存在 返回1表示存在
int BloomFilterFind(BloomFilter* bf, KeyType key)
{
	assert(bf);
	size_t index1 = bf->_hashfunc1(key);
	size_t index2 = bf->_hashfunc2(key);
	size_t index3 = bf->_hashfunc3(key);
	if (BitMapFind(&bf->_bm, index1) 
		&& BitMapFind(&bf->_bm, index1) 
		&& BitMapFind(&bf->_bm, index1))
	{
		return 1;
	}
	return 0;
}

void BloomFilterDestory(BloomFilter* bf)
{
	assert(bf);
	BitMapDestory(&bf->_bm);
}

void test()
{
	BloomFilter bf;
	BloomFilterInit(&bf, INT_MAX);

	BloomFilterSet(&bf, "sada");
	BloomFilterSet(&bf, "sdfd");
	BloomFilterSet(&bf, "gfdd");
	BloomFilterSet(&bf, "fdre");
	BloomFilterSet(&bf, "eedf");
	BloomFilterSet(&bf, "sfer");
	BloomFilterSet(&bf, "trhr");
	BloomFilterSet(&bf, "fewf");
	BloomFilterSet(&bf, "rege");
	BloomFilterSet(&bf, "weqf");


	printf("%s:%d\n", "sada", BloomFilterFind(&bf, "sada"));
	printf("%s:%d\n", "sdfd", BloomFilterFind(&bf, "sdfd"));
	printf("%s:%d\n", "gfdd", BloomFilterFind(&bf, "gfdd"));
	printf("%s:%d\n", "fdre", BloomFilterFind(&bf, "fdre"));
	printf("%s:%d\n", "eedf", BloomFilterFind(&bf, "eedf"));
	printf("%s:%d\n", "sfer", BloomFilterFind(&bf, "sfer"));
	printf("%s:%d\n", "a", BloomFilterFind(&bf, "a"));
	printf("%s:%d\n", "b", BloomFilterFind(&bf, "b"));

}

int main()
{
	test();
	system("pause");
	return 0;
}