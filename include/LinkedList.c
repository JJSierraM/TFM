#include "LinkedList.h"

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

NodeSize_t *LinkedListSize_tGoFirst (LinkedListSize_t *linked_list) {
    linked_list->current = linked_list->first;
    return linked_list->current;
}

NodeSize_t *LinkedListSize_tGoLast (LinkedListSize_t *linked_list) {
    linked_list->current = linked_list->last;
    return linked_list->current;
}

NodeSize_t *LinkedListSize_tNext (LinkedListSize_t *linked_list) {
    linked_list->current = linked_list->current->next;
    return linked_list->current;
}

NodeSize_t *LinkedListSize_tPrev (LinkedListSize_t *linked_list) {
    linked_list->current = linked_list->current->prev;
    return linked_list->current;
}

LinkedListSize_t LinkedListSize_tNew () {
    LinkedListSize_t output;
    output.size = 0;
    output.current = NULL;
    output.first = NULL;
    output.last = NULL;
    return output;
}

void LinkedListSize_tAppend(LinkedListSize_t *list, size_t value) {
    list->size++;
    NodeSize_t *node = (NodeSize_t*) malloc(sizeof(NodeSize_t));
    *node = (NodeSize_t) {
        value,
        NULL,
        list->last
    };
    list->last = node;
}

void LikedListSize_tAppendList(LinkedListSize_t *a, LinkedListSize_t *b) {
    a->size += b->size;
    a->last->next = b->first;
    a->last = b->last;
}

void LinkedListSize_tFree(LinkedListSize_t *list) {
    LinkedListSize_tGoLast(list);
    LinkedListSize_tPrev(list);
    while (list->current->prev != NULL) {
        free(list->current->next);
        LinkedListSize_tPrev(list);
    }    
    free(list->current);
    free(list);
}

ArraySize_t LinkedListSize_tToArray(LinkedListSize_t *list) {
    ArraySize_t output = ArraySize_tNew(list->size);
    LinkedListSize_tGoFirst(list);
    for (size_t i = 0; i < list->size; i++) {
        output.array[i] = LinkedListSize_tNext(list);
    }
    return output;
}

ArraySize_t LinkedListSize_tToArrayAndFree(LinkedListSize_t *list) {
    ArraySize_t output = LinkedListSize_tToArray(list);
    LinkedListSize_tFree(list);
    return output;
}