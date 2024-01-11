#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t round_up_to_power_of_2(size_t num)
{
    if (num == 0)
    {
        return -1;
    }

    num--;
    num |= (num >> 1);
    num |= (num >> 2);
    num |= (num >> 4);
    num |= (num >> 8);
    num |= (num >> 16);

    return num + 1;
}

Vector *vector_new(const size_t capacity, const size_t stride)
{
    Vector *v = malloc(sizeof(Vector));
    if (v == NULL)
    {
        return NULL;
    }

    void *arr = malloc(stride * capacity);
    if (arr == NULL)
    {
        free(v);
        return NULL;
    }

    v->stride = stride;
    v->capacity = (capacity == 0) ? 1 : capacity;
    v->size = 0;
    v->array = arr;

    return v;
}

void vector_free(Vector *v)
{
    if (v == NULL)
    {
        return;
    }
    free(v->array);
    free(v);
}

int vector_resize(Vector *v, size_t n)
{
    if (v == NULL)
    {
        return -1;
    }

    n = n == 0 ? 1 : n;

    void *temp = realloc(v->array, n * v->stride);
    if (temp == NULL)
    {
        return -1;
    }

    v->array = temp;
    v->capacity = n;

    return 0;
}

int vector_push_back(Vector *v, const void *data)
{
    if (v == NULL)
    {
        return -1;
    }

    if (v->size == v->capacity)
    {
        int err = vector_resize(v, v->capacity * GROWTH_FACTOR);
        if (err != 0)
        {
            return -1;
        }
    }

    void *dest = memcpy(v->array + (v->size * v->stride), data, v->stride);
    if (dest == NULL)
    {
        return -1;
    }

    v->size++;

    return 0;
}

int vector_pop_back(Vector *v)
{
    if (v == NULL)
    {
        return -1;
    }

    v->size--;

    if (v->size <= v->capacity / GROWTH_FACTOR)
    {
        int err = vector_resize(v, round_up_to_power_of_2(v->capacity / GROWTH_FACTOR));
        if (err != 0)
        {
            return -1;
        }
    }

    return 0;
}
