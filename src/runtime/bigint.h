#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {
    Vector digits;
    char sign;
} BigInt;

void bigInt_init(BigInt *bi);
void bigInt_free(BigInt *bi);
char bigInt_comp(BigInt *a, BigInt *b)
void bigInt_add(BigInt *a, BigInt *b, BigInt *result);
void bigInt_sub(BigInt *a, BigInt *b, BigInt *result);
void bigInt_mul(bigInt *a, BigInt *b, BigInt *result);
void bigInt_div(BigInt *a, BigInt *b, BigInt *result_quotient, BigInt *result_remainder);

#endif // !_BIGINT_H_
