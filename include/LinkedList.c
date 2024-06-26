#include "LinkedList.h"
#include "Debug.h"

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
    NodeSize_t *node = (NodeSize_t*) malloc(sizeof(NodeSize_t));
    *node = (NodeSize_t) {
        value,
        NULL,
        list->last
    };
    if (list->size == 0) {
        list->first = node;
    }
    else {
        list->last->next = node;
    }
    list->last = node;
    list->size++;
}

void LikedListSize_tAppendList(LinkedListSize_t *a, LinkedListSize_t *b) {
    a->size += b->size;
    a->last->next = b->first;
    a->last = b->last;
}

void LinkedListSize_tFree(LinkedListSize_t *list) {
    LinkedListSize_tGoLast(list);
    if (list->current->prev != NULL) {
        LinkedListSize_tPrev(list);
        while (list->current->prev != NULL) {
            free(list->current->next);
            LinkedListSize_tPrev(list);
        }    
    }
    free(list->current);
}

ArraySize_t LinkedListSize_tToArray(LinkedListSize_t *list) {
    // DEBUG_PRINTLN("Size of list: %ld", list->size)
    size_t lsize  = list->size;
    ArraySize_t output = ArraySize_tNew(lsize);
    if(lsize == 0){
        return output;
    } else{
        LinkedListSize_tGoFirst(list);
        output.array[0] = list->current->value;
        for (size_t i = 1; i < list->size; i++) {
            LinkedListSize_tNext(list);
            output.array[i] = list->current->value;
        }
        return output;
    }
}

ArraySize_t LinkedListSize_tToArrayAndFree(LinkedListSize_t *list) {
    ArraySize_t output = LinkedListSize_tToArray(list);
    LinkedListSize_tFree(list);
    return output;
}

NodeVector3Size_t *LinkedListVector3Size_tGoFirst (LinkedListVector3Size_t *linked_list) {
    linked_list->current = linked_list->first;
    return linked_list->current;
}

NodeVector3Size_t *LinkedListVector3Size_tGoLast (LinkedListVector3Size_t *linked_list) {
    linked_list->current = linked_list->last;
    return linked_list->current;
}

NodeVector3Size_t *LinkedListVector3Size_tNext (LinkedListVector3Size_t *linked_list) {
    linked_list->current = linked_list->current->next;
    return linked_list->current;
}

NodeVector3Size_t *LinkedListVector3Size_tPrev (LinkedListVector3Size_t *linked_list) {
    linked_list->current = linked_list->current->prev;
    return linked_list->current;
}

LinkedListVector3Size_t LinkedListVector3Size_tNew () {
    LinkedListVector3Size_t output;
    output.size = 0;
    output.current = NULL;
    output.first = NULL;
    output.last = NULL;
    return output;
}

void LinkedListVector3Size_tAppend(LinkedListVector3Size_t *list, Vector3Size_t value) {
    NodeVector3Size_t *node = (NodeVector3Size_t*) malloc(sizeof(NodeVector3Size_t));
    *node = (NodeVector3Size_t) {
        value,
        NULL,
        list->last
    };
    if (list->size == 0) {
        list->first = node;
    }
    else {
        list->last->next = node;
    }
    list->last = node;
    list->size++;
}

void LikedListVector3Size_tAppendList(LinkedListVector3Size_t *a, LinkedListVector3Size_t *b) {
    a->size += b->size;
    a->last->next = b->first;
    a->last = b->last;
}

void LinkedListVector3Size_tFree(LinkedListVector3Size_t *list) {
    LinkedListVector3Size_tGoLast(list);
    if (list->current->prev != NULL) {
        LinkedListVector3Size_tPrev(list);
        while (list->current->prev != NULL) {
            free(list->current->next);
            LinkedListVector3Size_tPrev(list);
        }    
    }
    free(list->current);
}

ArraySize_t LinkedListVector3Size_tToArray(LinkedListVector3Size_t *list) {
    // DEBUG_PRINTLN("Size of list: %ld", list->size)
    size_t lsize  = list->size;
    ArraySize_t output = ArraySize_tNew(3 * lsize);
    if(lsize == 0){
        return output;
    } else{
        LinkedListVector3Size_tGoFirst(list);
        output.array[0] = list->current->value.x;
        output.array[1] = list->current->value.y;
        output.array[2] = list->current->value.z;
        for (size_t i = 1; i < list->size; i++) {
            LinkedListVector3Size_tNext(list);
            output.array[3*i+0] = list->current->value.x;
            output.array[3*i+1] = list->current->value.y;
            output.array[3*i+2] = list->current->value.z;
        }
        return output;
    }
}

ArraySize_t LinkedListVector3Size_tToArrayAndFree(LinkedListVector3Size_t *list) {
    ArraySize_t output = LinkedListVector3Size_tToArray(list);
    LinkedListVector3Size_tFree(list);
    return output;
}
