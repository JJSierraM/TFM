#include <math.h>
#include <stdio.h>

typedef struct NodeSize_t
{
    size_t value;
    NodeSize_t *next;
    NodeSize_t *prev;
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

size_t* LinkedListSize_tToArray(LinkedListSize_t *list) ;

void LinkedListSize_tFree(LinkedListSize_t *list) ;