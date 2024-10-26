#include "../src/runtime/vector.h"

int main() {
    Vector v;
    vector_init(&v);

    vector_push_back(&v, 1);
    vector_push_back(&v, 2);
    vector_push_back(&v, 3);
    vector_push_back(&v, 4);

    vector_print(&v); // 打印: 1 2 3 4

    vector_erase(&v, 1); // 删除第二个元素
    vector_print(&v); // 打印: 1 3 4

    unsigned int value = vector_at(&v, 2);
    printf("Value at index 2: %u\n", value); // 打印: Value at index 2: 4

    vector_free(&v);
    return 0;
}


