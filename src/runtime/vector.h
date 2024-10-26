#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 10

typedef struct {
    unsigned int *data;
    size_t size;
    size_t capacity;
} Vector;

void vector_init(Vector *v);
void vector_push_back(Vector *v, unsigned int value);
unsigned int vector_at(Vector *v, size_t index);
void vector_erase(Vector *v, size_t index);
void vector_free(Vector *v);


#endif // !_VECTOR_H_


