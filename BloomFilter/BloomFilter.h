#ifndef _BLOOMFILTER_H_
#define _BLOOMFILTER_H_
#include "BitMap.h"


typedef const char* KeyType;

typedef size_t(*HASH_FUNC)(KeyType str);

typedef struct BloomFilter
{
	BitMap _bm;

	//hashº¯Êý
	HASH_FUNC _hashfunc1;
	HASH_FUNC _hashfunc2;
	HASH_FUNC _hashfunc3;
}BloomFilter;

void BloomFilterInit(BloomFilter* bf, size_t range);
void BloomFilterSet(BloomFilter* bf, KeyType key);
int BloomFilterFind(BloomFilter* bf, KeyType key);
void BloomFilterDestory(BloomFilter* bf);


#endif 
