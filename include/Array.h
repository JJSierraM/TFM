#include <stdio.h>
#include <stdlib.h>

#ifndef ARRAY
#define ARRAY

typedef struct ArraySize_t
{
    size_t size;
    size_t *array;
} ArraySize_t;

ArraySize_t ArraySize_tNew (size_t size) ;

ArraySize_t ArraySize_tZeros (size_t size) ;

void ArraySize_tFree (ArraySize_t *array) ;

ArraySize_t ArraySize_tAppendArrays (const ArraySize_t *a, const ArraySize_t *b) ;

void ArraySize_tPrint(ArraySize_t *array) ;

#endif