#include "vector.h"

void vector_init(Vector *v) {
    v->data = (uint64_t *)malloc(INITIAL_CAPACITY * sizeof(uint64_t));
    if (v->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    v->size = 0;
    v->capacity = INITIAL_CAPACITY;
}


uint64_t vector_size(Vector* v) {
    return v->size;
}

void vector_resize(Vector *v, size_t new_capacity) {
    uint64_t *new_data = (uint64_t *)realloc(v->data, new_capacity * sizeof(uint64_t));
    if (new_data == NULL) {
        fprintf(stderr, "Memory reallocation failed\n");
        exit(EXIT_FAILURE);
    }
    v->data = new_data;
    v->capacity = new_capacity;
}

void vector_push_back(Vector *v, uint64_t value) {
    if (v->size == v->capacity) {
        vector_resize(v, v->capacity == 0 ? INITIAL_CAPACITY : v->capacity * 2);
    }
    v->data[v->size++] = value;
}

uint64_t vector_at(Vector *v, size_t index) {
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

char vector_empty(Vector* v) {
    if (v == NULL) {
        fprintf(stderr, "Invalid arguments to vector_empty\n");
        exit(EXIT_FAILURE);
    }
    return (v->size == 0) ? 1 : 0;
}

uint64_t vector_back(Vector *v) {
    if (v->size == 0) {
        fprintf(stderr, "Vector is empty\n");
        exit(EXIT_FAILURE);
    }
    return v->data[v->size - 1];
}

// 移除 Vector 的最后一个元素
void vector_pop_back(Vector *v) {
    if (v->size == 0) {
        fprintf(stderr, "Vector is empty\n");
        exit(EXIT_FAILURE);
    }
    v->size--;
}

void vector_set(Vector *v, size_t index, uint64_t value) {
    if (index >= v->size) {
        fprintf(stderr, "Index out of range\n");
        exit(EXIT_FAILURE);
    }
    v->data[index] = value;
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

