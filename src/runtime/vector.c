#include "vector.h"

void vector_init(Vector *v) {
    v->data = (unsigned int *)malloc(INITIAL_CAPACITY * sizeof(unsigned int));
    if (v->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    v->size = 0;
    v->capacity = INITIAL_CAPACITY;
}

static void vector_resize(Vector *v, size_t new_capacity) {
    unsigned int *new_data = (unsigned int *)realloc(v->data, new_capacity * sizeof(unsigned int));
    if (new_data == NULL) {
        fprintf(stderr, "Memory reallocation failed\n");
        exit(EXIT_FAILURE);
    }
    v->data = new_data;
    v->capacity = new_capacity;
}

void vector_push_back(Vector *v, unsigned int value) {
    if (v->size == v->capacity) {
        vector_resize(v, v->capacity == 0 ? INITIAL_CAPACITY : v->capacity * 2);
    }
    v->data[v->size++] = value;
}

unsigned int vector_at(Vector *v, size_t index) {
    if (index >= v->size) {
        fprintf(stderr, "Index out of range\n");
        exit(EXIT_FAILURE);
    }
    return v->data[index];
}

void vector_erase(Vector *v, size_t index) {
    if (index >= v->size) {
        fprintf(stderr, "Index out of range\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i = index; i < v->size - 1; ++i) {
        v->data[i] = v->data[i + 1];
    }
    v->size--;
}

void vector_free(Vector *v) {
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

void vector_print(Vector *v) {
    for (size_t i = 0; i < v->size; ++i) {
        printf("%u ", v->data[i]);
    }
    printf("\n");
}

