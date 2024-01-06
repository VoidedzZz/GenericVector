#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main(int argc, char* argv[])
{

    Vector *myvec = vector_new(4, sizeof(int));
    if (myvec == NULL)
    {
        fprintf(stderr, "Error: unable to init. vector\n");
        exit(EXIT_FAILURE);
    }

    printf("Size: %zu; Capacity: %zu;\n", myvec->size, myvec->capacity);

    int i = 1;
    vector_push_back(myvec, &i);
    vector_push_back(myvec, &i);
    vector_push_back(myvec, &i);
    vector_push_back(myvec, &i);

    printf("Size: %zu; Capacity: %zu;\n", myvec->size, myvec->capacity);

    vector_push_back(myvec, &i);

    printf("Size: %zu; Capacity: %zu;\n", myvec->size, myvec->capacity);

    int err = vector_push_back(NULL, &i);
    if (err != 0)
    {
        fprintf(stderr, "Error: unable to push to vector\n");
        vector_free(myvec);
        exit(EXIT_FAILURE);
    }

    vector_free(myvec);
    return 0;
}
