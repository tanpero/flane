#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define VECTOR_INIT_CAPACITY 2


// Vector structure to store elements of a dynamic array
typedef struct {
    uint64_t *elements; // Pointer to the array of elements
    size_t size;       // Current number of elements
    size_t capacity;   // Total capacity of the array
} Vector;

// BigInt structure to represent large integers
typedef struct {
    Vector digits;    // Vector to store the digits of the integer
    char sign;        // Sign of the integer, '1' for positive, '-1' for negative
} BigInt;

// Initializes a Vector
void vector_init(Vector *v);

// Pushes a value to the end of a Vector
void vector_push_back(Vector *v, uint64_t value);

// Gets the value at a specific index in a Vector
uint64_t vector_get(const Vector *v, size_t index);

// Pops the last element from a Vector
void vector_pop_back(Vector *v);

// Clears a Vector, freeing its memory
void vector_clear(Vector *v);

// Destroys a Vector, equivalent to clearing it
void vector_destroy(Vector *v);

// Initializes a BigInt
void bigint_init(BigInt *bi);

// Destroys a BigInt, freeing its memory
void bigint_destroy(BigInt *bi);

// Sets a digit in the Vector at a specific index
void vector_set(Vector *v, size_t index, uint64_t value);

// Converts a string to a BigInt
void bigint_from_string(BigInt *bi, const char *str);

// Converts an integer to a BigInt
void bigint_from_int(BigInt *bi, int value);

// Prints a BigInt
void bigint_print(const BigInt *bi);

#endif // _BIGINT_H_