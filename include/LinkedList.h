#include <math.h>
#include <stdlib.h>
#include "Array.h"
#include "Vector.h"

#ifndef LINKED_LIST
#define LINKED_LIST

typedef struct NodeSize_t
{
    size_t value;
    void *next;
    void *prev;
} NodeSize_t;

typedef struct LinkedListSize_t
{
    size_t size;
    NodeSize_t *current;
    NodeSize_t *first;
    NodeSize_t *last;
} LinkedListSize_t;

NodeSize_t *LinkedListSize_tGoFirst (LinkedListSize_t *linked_list) ;

NodeSize_t *LinkedListSize_tGoLast (LinkedListSize_t *linked_list) ;

NodeSize_t *LinkedListSize_tNext (LinkedListSize_t *linked_list) ;

NodeSize_t *LinkedListSize_tPrev (LinkedListSize_t *linked_list) ;

LinkedListSize_t LinkedListSize_tNew () ;

void LinkedListSize_tAppend(LinkedListSize_t *list, size_t value) ;

void LikedListSize_tAppendList(LinkedListSize_t *a, LinkedListSize_t *b) ;

void LinkedListSize_tFree(LinkedListSize_t *list) ;

ArraySize_t LinkedListSize_tToArray(LinkedListSize_t *list) ;

ArraySize_t LinkedListSize_tToArrayAndFree(LinkedListSize_t *list) ;

typedef struct NodeVector3Size_t
{
    Vector3Size_t value;
    void *next;
    void *prev;
} NodeVector3Size_t;

typedef struct LinkedListVector3Size_t
{
    size_t size;
    NodeVector3Size_t *current;
    NodeVector3Size_t *first;
    NodeVector3Size_t *last;
} LinkedListVector3Size_t;

NodeVector3Size_t *LinkedListVector3Size_tGoFirst (LinkedListVector3Size_t *linked_list) ;

NodeVector3Size_t *LinkedListVector3Size_tGoLast (LinkedListVector3Size_t *linked_list) ;

NodeVector3Size_t *LinkedListVector3Size_tNext (LinkedListVector3Size_t *linked_list) ;

NodeVector3Size_t *LinkedListVector3Size_tPrev (LinkedListVector3Size_t *linked_list) ;

LinkedListVector3Size_t LinkedListVector3Size_tNew () ;

void LinkedListVector3Size_tAppend(LinkedListVector3Size_t *list, Vector3Size_t value) ;

void LikedListVector3Size_tAppendList(LinkedListVector3Size_t *a, LinkedListVector3Size_t *b) ;

void LinkedListVector3Size_tFree(LinkedListVector3Size_t *list) ;

ArraySize_t LinkedListVector3Size_tToArray(LinkedListVector3Size_t *list) ;

ArraySize_t LinkedListVector3Size_tToArrayAndFree(LinkedListVector3Size_t *list) ;

#endif