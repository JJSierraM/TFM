#include <stdio.h>
#include <stdlib.h>
#include "Vector.h"

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

void ArraySize_tAppendArrays (ArraySize_t *a, const ArraySize_t *b) ;

void ArraySize_tPrint(ArraySize_t *array) ;

typedef struct ArrayVector2
{
    size_t size;
    Vector2 *array;
} ArrayVector2;

ArrayVector2 ArrayVector2New (const size_t size) ;

ArrayVector2 ArrayVector2Zeros (const size_t size) ;

void ArrayVector2Free (ArrayVector2 *array) ;

void ArrayVector2AppendArrays (ArrayVector2 *a, const ArrayVector2 *b) ;

void ArrayVector2Print(ArrayVector2 *array) ;

typedef struct ArrayVector3
{
    size_t size;
    Vector3 *array;
} ArrayVector3;

ArrayVector3 ArrayVector3New (const size_t size) ;

ArrayVector3 ArrayVector3Zeros (const size_t size) ;

void ArrayVector3Free (ArrayVector3 *array) ;

void ArrayVector3AppendArrays (ArrayVector3 *a, const ArrayVector3 *b) ;

void ArrayVector3Print(ArrayVector3 *array) ;

#endif