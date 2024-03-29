#include "Array.h"

ArraySize_t ArraySize_tNew (const size_t size) {
    ArraySize_t output;
    output.size = size;
    output.array = (size_t*) malloc(size * sizeof(size_t));
    return output;
}

ArraySize_t ArraySize_tZeros (const size_t size) {
    ArraySize_t output;
    output.size = size;
    output.array = (size_t*) calloc(size, sizeof(size_t));
    return output;
}

void ArraySize_tFree (ArraySize_t *array) {
    free(array->array);
}

ArraySize_t ArraySize_tAppendArrays (const ArraySize_t *a, const ArraySize_t *b) {
    size_t i, j;
    ArraySize_t output;
    output.size = a->size + b->size;
    output.array = (size_t*) malloc(output.size * sizeof(size_t));

    for (i = 0; i < a->size; i++) {
        output.array[i] = a->array[i];
    }
    for (j = 0; j < b->size; j++) {
        output.array[i+j] = b->array[j];
    }
    return output;
}

void ArraySize_tPrint(ArraySize_t *array) {
    printf("Array size: %lu\n", array->size);
    printf("Array content: [\n");
    for (size_t i = 0; i < array->size; i++) {
        printf(" %4lu\n", array->array[i]);
    }
    printf("]\n");
}
