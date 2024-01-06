#pragma once
#include <stdlib.h>

typedef struct Vector
{
    size_t stride;
    size_t capacity;
    size_t size;
    void *array;
} Vector;

extern Vector *vector_new(const size_t capacity, const size_t stride);

extern void vector_free(Vector *v);

extern int vector_resize(Vector *v, const size_t n);

extern int vector_push_back(Vector *v, const void *data);

extern int vector_pop_back(Vector *v);
