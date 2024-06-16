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

void ArraySize_tAppendArrays (ArraySize_t *a, const ArraySize_t *b) {
    size_t j;
    a->array = realloc(a->array, (a->size+b->size) * sizeof(size_t));

    for (j = 0; j < b->size; j++) {
        a->array[a->size+j] = b->array[j];
    }
    a->size += b->size;
}

void ArraySize_tPrint(ArraySize_t *array) {
    printf("Array size: %lu\n", array->size);
    printf("Array content: [\n");
    for (size_t i = 0; i < array->size; i++) {
        printf(" %4lu\n", array->array[i]);
    }
    printf("]\n");
}

ArrayVector2 ArrayVector2New (const size_t size) {
    ArrayVector2 output;
    output.size = size;
    output.array = (Vector2*) malloc(size * sizeof(Vector2));
    return output;
}

ArrayVector2 ArrayVector2Zeros (const size_t size) {
    ArrayVector2 output;
    output.size = size;
    output.array = (Vector2*) calloc(size, sizeof(Vector2));
    return output;
}

void ArrayVector2Free (ArrayVector2 *array) {
    free(array->array);
}

void ArrayVector2AppendArrays (ArrayVector2 *a, const ArrayVector2 *b) {
    size_t j;
    a->array = realloc(a->array, (a->size+b->size) * sizeof(Vector2));

    for (j = 0; j < b->size; j++) {
        a->array[a->size+j] = b->array[j];
    }
    a->size += b->size;
}

void ArrayVector2Print(ArrayVector2 *array) {
    printf("Array size: %lu\n", array->size);
    printf("Array content: [\n");
    for (size_t i = 0; i < array->size; i++) {
        printf(" (%4f, %4f)\n", array->array[i].x, array->array[i].y);
    }
    printf("]\n");
}

ArrayVector3 ArrayVector3New (const size_t size) {
    ArrayVector3 output;
    output.size = size;
    output.array = (Vector3*) malloc(size * sizeof(Vector3));
    return output;
}

ArrayVector3 ArrayVector3Zeros (const size_t size) {
    ArrayVector3 output;
    output.size = size;
    output.array = (Vector3*) calloc(size, sizeof(Vector3));
    return output;
}

void ArrayVector3Free (ArrayVector3 *array) {
    free(array->array);
}

ArrayVector3 ArrayVector3AppendArrays (const ArrayVector3 *a, const ArrayVector3 *b) {
    size_t i, j;
    ArrayVector3 output;
    output.size = a->size + b->size;
    output.array = (Vector3*) malloc(output.size * sizeof(Vector3));

    for (i = 0; i < a->size; i++) {
        output.array[i] = a->array[i];
    }
    for (j = 0; j < b->size; j++) {
        output.array[i+j] = b->array[j];
    }
    return output;
}

void ArrayVector3AppendArrays (ArrayVector3 *a, const ArrayVector3 *b) {
    size_t j;
    a->array = realloc(a->array, (a->size+b->size) * sizeof(Vector3));

    for (j = 0; j < b->size; j++) {
        a->array[a->size+j] = b->array[j];
    }
    a->size += b->size;
}

void ArrayVector3Print(ArrayVector3 *array) {
    printf("Array size: %lu\n", array->size);
    printf("Array content: [\n");
    for (size_t i = 0; i < array->size; i++) {
        printf(" (%4f, %4f)\n", array->array[i].x, array->array[i].y);
    }
    printf("]\n");
}