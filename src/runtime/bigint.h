#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "vector.h"

typedef struct {
    Vector* digits;
    char sign; // 1 for positive, -1 for negative
} BigInt;


void bigInt_init(BigInt *bi);
void bigInt_free(BigInt *bi);
char bigInt_comp(BigInt *a, BigInt *b);
void bigInt_neg(BigInt *a);
void bigInt_add(BigInt *a, BigInt *b, BigInt *result);
void bigInt_sub(BigInt *a, BigInt *b, BigInt *result);
void bigInt_mul(BigInt *a, BigInt *b, BigInt *result);
void bigInt_div(BigInt *a, BigInt *b, BigInt *result_quotient, BigInt *result_remainder);
BigInt* fromString(char* s);
char* toString(BigInt n);


#endif // !_BIGINT_H_
