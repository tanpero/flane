#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define INITIAL_CAPACITY 10

typedef struct {
    uint64_t *data;
    size_t size;
    size_t capacity;
} Vector;

void vector_init(Vector *v);
uint64_t vector_size(Vector* v);
void vector_resize(Vector *v, size_t new_capacity);
void vector_push_back(Vector *v, uint64_t value);
uint64_t vector_at(Vector *v, size_t index);
void vector_erase(Vector *v, size_t index);
char vector_empty(Vector* v);
uint64_t vector_back(Vector *v);
void vector_pop_back(Vector *v);
void vector_set(Vector *v, size_t index, uint64_t value);
void vector_free(Vector *v);


#endif // !_VECTOR_H_


