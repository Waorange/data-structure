#ifndef _BITMAP_H_
#define _BITMAP_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct BitMap {
	size_t * _bits;
	size_t _range; //��Ҫ�����������ֵ
}BitMap;

void BitMapInit(BitMap * bm, size_t range);  
void BitMapSet(BitMap * bm, size_t x);
void BitMapReset(BitMap * bm, size_t x);
void BitMapDestory(BitMap * bm);

#endif