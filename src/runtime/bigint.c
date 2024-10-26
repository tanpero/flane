#include "bigint.h"

void bigInt_init(BigInt *bi) {
    vector_init(&bi->digits);
    bi->sign = '0'; // Default to positive
}

void bigInt_free(BigInt *bi) {
    vector_free(&bi->digits);
}
static void ensure_capacity(Vector *v, size_t capacity) {
    if (v->capacity < capacity) {
        size_t new_capacity = capacity * 2;
        unsigned int *new_data = realloc(v->data, new_capacity * sizeof(unsigned int));
        if (new_data) {
            v->data = new_data;
            v->capacity = new_capacity;
        } else {
            fprintf(stderr, "Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
    }
}


// Helper function to add two unsigned integers
static inline unsigned int add_uint(unsigned int a, unsigned int b, int *carry) {
    unsigned int sum = a + b;
    *carry = (sum < a) || (sum < b);
    return sum;
}

// Helper function to subtract two unsigned integers
static inline unsigned int sub_uint(unsigned int a, unsigned int b, int *borrow) {
    unsigned int diff = a - b;
    *borrow = (diff > a);
    return diff;
}


void bigInt_add(BigInt *a, BigInt *b, BigInt *result) {
    bigInt_init(result);
    result->sign = (a->sign == b->sign) ? a->sign : '0'; // Positive if signs are the same, otherwise 0 (undefined)

    size_t max_size = a->digits.size > b->digits.size ? a->digits.size : b->digits.size;
    ensure_capacity(&a->digits, max_size);
    ensure_capacity(&b->digits, max_size);
    ensure_capacity(&result->digits, max_size);

    int carry = 0;
    for (size_t i = 0; i < max_size; i++) {
        unsigned int digit_a = i < a->digits.size ? vector_at(&a->digits, i) : 0;
        unsigned int digit_b = i < b->digits.size ? vector_at(&b->digits, i) : 0;
        unsigned int sum = add_uint(digit_a, digit_b, &carry);
        vector_push_back(&result->digits, sum);
    }

    if (carry) {
        vector_push_back(&result->digits, 1);
    }

    // Remove leading zeros
    while (result->digits.size > 1 && vector_at(&result->digits, result->digits.size - 1) == 0) {
        vector_erase(&result->digits, result->digits.size - 1);
    }
}

void bigInt_sub(BigInt *a, BigInt *b, BigInt *result) {
    bigInt_init(result);
    if (a->sign != b->sign) {
        bigInt_add(a, b, result);
        result->sign = a->sign;
        return;
    }

    int a_is_greater = 1;
    BigInt temp_b = {0};
    bigInt_init(&temp_b);

    if (a->sign == '1') { // If both are negative, make them positive for subtraction
        a->sign = '0';
        b->sign = '0';
    }

    if (b->digits.size > a->digits.size || (b->digits.size == a->digits.size && vector_at(&b->digits, b->digits.size - 1) > vector_at(&a->digits, a->digits.size - 1))) {
        a_is_greater = 0;
        bigInt_add(a, b, &temp_b);
        bigInt_add(&temp_b, b, result);
        result->sign = '1';
    } else {
        bigInt_add(a, b, &temp_b);
        bigInt_add(&temp_b, a, result);
    }

    bigInt_free(&temp_b);

    if (!a_is_greater) {
        result->sign = '1';
    }

    // Remove leading zeros
    while (result->digits.size > 1 && vector_at(&result->digits, result->digits.size - 1) == 0) {
        vector_erase(&result->digits, result->digits.size - 1);
    }
}

static inline void bigInt_primary_mul(BigInt *a, BigInt *b, BigInt *result) {
    bigInt_init(result);
    result->sign = (a->sign == b->sign) ? a->sign : '0'; // Positive if signs are the same, otherwise 0

    size_t max_size = a->digits.size + b->digits.size;
    ensure_capacity(&result->digits, max_size);

    // Initialize result array with zeros
    for (size_t i = 0; i < max_size; i++) {
        vector_push_back(&result->digits, 0);
    }

    // Perform multiplication
    for (size_t i = 0; i < a->digits.size; i++) {
        for (size_t j = 0; j < b->digits.size; j++) {
            unsigned int digit_a = vector_at(&a->digits, i);
            unsigned int digit_b = vector_at(&b->digits, j);
            unsigned int carry = 0;
            unsigned int sum = add_uint(vector_at(&result->digits, i + j), digit_a * digit_b, &carry);
            sum = add_uint(sum, carry, &carry);
            vector_set(&result->digits, i + j, sum);
            // Propagate the carry to the next digit
            if (i + j + 1 < max_size) {
                unsigned int next_carry = 0;
                unsigned int next_sum = add_uint(vector_at(&result->digits, i + j + 1), carry, &next_carry);
                vector_set(&result->digits, i + j + 1, next_sum);
                if (carry) {
                    if (i + j + 2 < max_size) {
                        unsigned int next_next_carry = 0;
                        unsigned int next_next_sum = add_uint(vector_at(&result->digits, i + j + 2), next_carry, &next_next_carry);
                        vector_set(&result->digits, i + j + 2, next_next_sum);
                    }
                }
            }
        }
    }

    // Remove leading zeros
    while (result->digits.size > 1 && vector_at(&result->digits, result->digits.size - 1) == 0) {
        vector_erase(&result->digits, result->digits.size - 1);
    }
}

void bigInt_mul(BigInt *a, BigInt *b, BigInt *result) {
    bigInt_primary_mul(a, b, result);
}


