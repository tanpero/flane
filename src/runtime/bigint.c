
#include "bigint.h"

typedef struct {
    uint64_t *elements;
    size_t size;
    size_t capacity;
} Vector;

void vector_init(Vector *v) {
    v->elements = (uint64_t *)malloc(VECTOR_INIT_CAPACITY * sizeof(uint64_t));
    if (v->elements == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    v->size = 0;
    v->capacity = VECTOR_INIT_CAPACITY;
}

void vector_push_back(Vector *v, uint64_t value) {
    if (v->size >= v->capacity) {
        size_t new_capacity = v->capacity * 2;
        uint64_t *new_elements = (uint64_t *)realloc(v->elements, new_capacity * sizeof(uint64_t));
        if (new_elements == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            exit(EXIT_FAILURE);
        }
        v->elements = new_elements;
        v->capacity = new_capacity;
    }
    v->elements[v->size++] = value;
}

uint64_t vector_get(const Vector *v, size_t index) {
    if (index >= v->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return v->elements[index];
}

void vector_pop_back(Vector *v) {
    if (v->size == 0) {
        fprintf(stderr, "Vector is empty\n");
        exit(EXIT_FAILURE);
    }
    v->size--;
}

void vector_clear(Vector *v) {
    free(v->elements);
    v->elements = NULL;
    v->size = 0;
    v->capacity = 0;
}

void vector_destroy(Vector *v) {
    vector_clear(v);
}

typedef struct {
    Vector digits;
    char sign; // '1' for positive, -1 for negative
} BigInt;

void bigint_init(BigInt *bi) {
    vector_init(&bi->digits);
    bi->sign = '1'; // default to positive
}

void bigint_destroy(BigInt *bi) {
    vector_destroy(&bi->digits);
}


// Helper function to set a digit in the vector
void vector_set(Vector *v, size_t index, uint64_t value) {
    if (index >= v->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    v->elements[index] = value;
}

// Converts a string to a BigInt
void bigint_from_string(BigInt *bi, const char *str) {
    bigint_init(bi);
    bi->sign = (*str == '-') ? -1 : '1';
    const char *ptr = (*str == '-') ? str + 1 : str;
    while (*ptr != '\0') {
        if (!isdigit((unsigned char)*ptr)) {
            fprintf(stderr, "Invalid character in string\n");
            exit(EXIT_FAILURE);
        }
        uint64_t digit = *ptr - '0';
        vector_push_back(&bi->digits, digit);
        ptr++;
    }
    // Reverse the digits
    for (size_t i = 0; i < bi->digits.size / 2; ++i) {
        uint64_t temp = vector_get(&bi->digits, i);
        vector_set(&bi->digits, i, vector_get(&bi->digits, bi->digits.size - 1 - i));
        vector_set(&bi->digits, bi->digits.size - 1 - i, temp);
    }
}

// Converts an integer to a BigInt
void bigint_from_int(BigInt *bi, int value) {
    bigint_init(bi);
    bi->sign = (value < 0) ? -1 : '1';
    uint64_t abs_value = (uint64_t)(value < 0 ? -value : value);
    do {
        vector_push_back(&bi->digits, abs_value % 10);
        abs_value /= 10;
    } while (abs_value > 0);
    // Reverse the digits
    for (size_t i = 0; i < bi->digits.size / 2; ++i) {
        uint64_t temp = vector_get(&bi->digits, i);
        vector_set(&bi->digits, i, vector_get(&bi->digits, bi->digits.size - 1 - i));
        vector_set(&bi->digits, bi->digits.size - 1 - i, temp);
    }
}


void bigint_print(const BigInt *bi) {
    if (bi->sign == -1) {
        printf("-");
    }
    for (int i = (int)bi->digits.size - 1; i >= 0; --i) {
        printf("%llu", vector_get(&bi->digits, i));
    }
}

// 比较两个 BigInt 的大小，返回 -1（小于），0（等于），1（大于）
int bigint_compare(const BigInt *a, const BigInt *b) {
    if (a->sign != b->sign) {
        return a->sign == -1 ? -1 : 1;
    }

    if (a->digits.size != b->digits.size) {
        return a->digits.size > b->digits.size ? 1 : -1;
    }

    for (int i = (int)a->digits.size - 1; i >= 0; --i) {
        uint64_t digit_a = vector_get(&a->digits, i);
        uint64_t digit_b = vector_get(&b->digits, i);
        if (digit_a != digit_b) {
            return digit_a > digit_b ? 1 : -1;
        }
    }

    return 0;
}

// 实现 BigInt 的加法运算
void bigint_add(BigInt *result, const BigInt *a, const BigInt *b) {
    if (a->sign != b->sign) {
        int cmp = bigint_compare(a, b);
        if (cmp == -1) {
            bigint_sub(result, b, a);
            result->sign = b->sign;
        } else {
            bigint_sub(result, a, b);
            result->sign = a->sign;
        }
        return;
    }

    result->sign = a->sign;
    uint64_t carry = 0;
    for (size_t i = 0; i < a->digits.size || carry; ++i) {
        uint64_t digit_a = i < a->digits.size ? vector_get(&a->digits, i) : 0;
        uint64_t digit_b = i < b->digits.size ? vector_get(&b->digits, i) : 0;
        uint64_t sum = digit_a + digit_b + carry;
        carry = sum / 10;
        vector_push_back(&result->digits, sum % 10);
    }
}

// 实现 BigInt 的减法运算
void bigint_sub(BigInt *result, const BigInt *a, const BigInt *b) {
    int cmp = bigint_compare(a, b);
    if (cmp == -1) {
        bigint_sub(result, b, a);
        result->sign = -1;
    } else if (cmp == 0) {
        vector_init(&result->digits);
        result->sign = '1';
    } else {
        BigInt temp;
        bigint_init(&temp);
        bigint_sub(&temp, b, a);
        result->digits = temp.digits; // 直接赋值，避免重复代码
        result->sign = a->sign;
        bigint_destroy(&temp);
    }
}

int main() {
    BigInt a, b, result_add, result_sub, result_add_negative, result_sub_negative;

    // 测试加法
    bigint_init(&a);
    bigint_init(&b);
    bigint_init(&result_add);
    bigint_init(&result_sub);
    bigint_init(&result_add_negative);
    bigint_init(&result_sub_negative);

    bigint_from_string(&a, "12345678901234567890");
    bigint_from_string(&b, "98765432109876543210");

    // 正数加正数
    bigint_add(&result_add, &a, &b);
    printf("Addition (Positive + Positive): ");
    bigint_print(&result_add);
    printf("\n");

    // 正数减正数
    bigint_sub(&result_sub, &a, &b);
    printf("Subtraction (Positive - Positive): ");
    bigint_print(&result_sub);
    printf("\n");

    // 测试负数加正数和减正数
    bigint_from_string(&a, "-12345678901234567890");
    bigint_from_string(&b, "98765432109876543210");

    // 负数加正数
    bigint_add(&result_add_negative, &a, &b);
    printf("Addition (Negative + Positive): ");
    bigint_print(&result_add_negative);
    printf("\n");

    // 负数减正数
    bigint_sub(&result_sub_negative, &a, &b);
    printf("Subtraction (Negative - Positive): ");
    bigint_print(&result_sub_negative);
    printf("\n");

    // 清理
    bigint_destroy(&a);
    bigint_destroy(&b);
    bigint_destroy(&result_add);
    bigint_destroy(&result_sub);
    bigint_destroy(&result_add_negative);
    bigint_destroy(&result_sub_negative);

    return 0;
}









