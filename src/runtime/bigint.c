#include "bigint.h"

#include "bigint.h"

// 初始化BigInt
void bigInt_init(BigInt *bi) {
    assert(bi != NULL);
    bi->digits = (Vector*)malloc(sizeof(Vector));
    vector_init(bi->digits);
    bi->sign = 1; // 默认为正数
}

// 释放BigInt资源
void bigInt_free(BigInt *bi) {
    assert(bi != NULL);
    vector_free(bi->digits);
    free(bi->digits);
    bi->digits = NULL;
    bi->sign = 0; // 重置符号
}

// 从字符串初始化BigInt
BigInt* fromString(char* s) {
    assert(s != NULL);
    BigInt *bi = (BigInt*)malloc(sizeof(BigInt));
    bigInt_init(bi);
    bi->sign = (*s == '-') ? -1 : 1;
    if (*s == '-') s++; // 跳过负号

    char *tmp = strdup(s);
    char *token = strtok(tmp, "0123456789");
    while (token != NULL) {
        vector_push_back(bi->digits, atoi(token));
        token = strtok(NULL, "0123456789");
    }
    free(tmp);

    return bi;
}

// 将BigInt转换为字符串
char* toString(BigInt n) {
    assert(n.digits != NULL);
    int length = vector_size(n.digits);
    if (length == 0) return strdup("0");

    // 计算所需字符长度（包括符号和结束符'\0'）
    int totalLength = length * 10; // 每个数字最多10位
    char *str = (char*)malloc(totalLength + 2); // 加2是为了符号和结束符
    str[0] = (n.sign == -1) ? '-' : '\0'; // 如果是负数，添加负号
    int index = (n.sign == -1) ? 1 : 0; // 字符串的起始位置

    for (int i = 0; i < length; ++i) {
        int digit = vector_at(n.digits, i);
        sprintf(&str[index], "%d", digit);
        index += (digit > 9) ? 2 : 1; // 更新索引位置
    }
    str[index] = '\0'; // 添加字符串结束符

    return str;
}
