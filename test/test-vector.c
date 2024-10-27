#include "../src/runtime/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 测试初始化和销毁
void test_init_and_free() {
    Vector v;
    vector_init(&v);
    assert(v.data != NULL);
    vector_free(&v);
    assert(v.data == NULL);
}

// 测试向量大小
void test_size() {
    Vector v;
    vector_init(&v);
    assert(vector_size(&v) == 0);
    vector_push_back(&v, 1);
    assert(vector_size(&v) == 1);
    vector_push_back(&v, 2);
    assert(vector_size(&v) == 2);
    vector_free(&v);
}

// 测试动态扩容
void test_resize() {
    Vector v;
    vector_init(&v);
    assert(v.capacity == INITIAL_CAPACITY);
    for (size_t i = 0; i < 2 * INITIAL_CAPACITY; ++i) {
        vector_push_back(&v, i);
    }
    assert(v.capacity > INITIAL_CAPACITY);
    vector_free(&v);
}

// 测试访问元素
void test_at() {
    Vector v;
    vector_init(&v);
    for (unsigned int i = 0; i < 10; ++i) {
        vector_push_back(&v, i);
    }
    for (size_t i = 0; i < vector_size(&v); ++i) {
        assert(vector_at(&v, i) == i);
    }
    vector_free(&v);
}

// 测试删除元素
void test_erase() {
    Vector v;
    vector_init(&v);
    for (unsigned int i = 0; i < 10; ++i) {
        vector_push_back(&v, i);
    }
    vector_erase(&v, 5);
    assert(vector_size(&v) == 9);
    for (size_t i = 5; i < vector_size(&v); ++i) {
        assert(vector_at(&v, i) == i + 1);
    }
    vector_free(&v);
}

// 测试检查空向量
void test_empty() {
    Vector v;
    vector_init(&v);
    assert(vector_empty(&v) == 1);
    vector_push_back(&v, 1);
    assert(vector_empty(&v) == 0);
    vector_free(&v);
}

// 测试获取最后一个元素
void test_back() {
    Vector v;
    vector_init(&v);
    for (unsigned int i = 0; i < 10; ++i) {
        vector_push_back(&v, i);
    }
    assert(vector_back(&v) == 9);
    vector_free(&v);
}

// 测试移除最后一个元素
void test_pop_back() {
    Vector v;
    vector_init(&v);
    for (unsigned int i = 0; i < 10; ++i) {
        vector_push_back(&v, i);
    }
    vector_pop_back(&v);
    assert(vector_size(&v) == 9);
    assert(vector_back(&v) == 8);
    vector_free(&v);
}

// 测试设置元素
void test_set() {
    Vector v;
    vector_init(&v);
    for (unsigned int i = 0; i < 10; ++i) {
        vector_push_back(&v, i);
    }
    vector_set(&v, 5, 100);
    assert(vector_at(&v, 5) == 100);
    vector_free(&v);
}

// 测试打印向量
void test_print() {
    Vector v;
    vector_init(&v);
    for (unsigned int i = 0; i < 10; ++i) {
        vector_push_back(&v, i);
    }
    vector_print(&v);
    vector_free(&v);
}

int main() {
    test_init_and_free();
    test_size();
    test_resize();
    test_at();
    test_erase();
    test_empty();
    test_back();
    test_pop_back();
    test_set();
    test_print();

    printf("All tests passed!\n");
    return 0;
}
