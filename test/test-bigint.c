#include "../src/runtime/bigint.h"

#include <stdio.h>
#include <stdlib.h>

// 测试从字符串创建BigInt对象
void testFromString() {
    char *testStr1 = "12345678901234567890";
    char *testStr2 = "-98765432109876543210";
    BigInt *bi1 = fromString(testStr1);
    BigInt *bi2 = fromString(testStr2);

    printf("BigInt from '%s': ", testStr1);
    char *str1 = toString(*bi1);
    printf("%s\n", str1);
    free(str1);

    printf("BigInt from '%s': ", testStr2);
    char *str2 = toString(*bi2);
    printf("%s\n", str2);
    free(str2);

    bigInt_free(bi1);
    bigInt_free(bi2);
}

int main() {
    testFromString();
    return 0;
}
