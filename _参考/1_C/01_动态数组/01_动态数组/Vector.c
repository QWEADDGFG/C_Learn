#include "Vector.h"	// "": 搜索路径：当前目录 -> 系统的头文件包含目录下
#include <stdlib.h> // <>: 搜索路径：系统的头文件包含目录下
#include <stdio.h>


#define DEFAULT_CAPACITY 8
#define PREALLOC_MAX  1024
// 创建空的动态数组
Vector* vector_create(void) {
    Vector* v = malloc(sizeof(Vector));
    if (!v) {
        printf("Error: malloc failed in vector_create\n");
        exit(1);
    }
    E* p = malloc(DEFAULT_CAPACITY * sizeof(E));
    if (!p) {
        free(v);
        printf("Error: malloc failed in vector_create\n");
        exit(1);
    }

    v->elements = p;
    v->capacity = DEFAULT_CAPACITY;
    v->size = 0;

    return v;
}
// 析构函数
void  vector_destroy(Vector* v) {
    // 按申请的相反顺序释放
    free(v->elements);  // 悬空指针
    free(v);
}

void grow_capacity(Vector* v) {
    int new_capacity = v->capacity < PREALLOC_MAX ? 
        v->capacity << 1 : v->capacity + PREALLOC_MAX;

    // 问题：realloc失败会返回NULL, 原来的内存空间不会被释放。
    // v->elements = realloc(v->elements, new_capacity * sizeof(E));
    E* p = realloc(v->elements, new_capacity * sizeof(E));
    if (!p) {
        printf("Error: realloc failed in realloc\n");
        exit(1);
    }
    // 更改动态数组的属性
    v->elements = p;
    v->capacity = new_capacity;
}

void push_back(Vector* v, E val) {
    // 判断是否需要扩容
    if (v->size == v->capacity) {
        grow_capacity(v);
    }
    // 添加元素val
    v->elements[v->size++] = val;
}