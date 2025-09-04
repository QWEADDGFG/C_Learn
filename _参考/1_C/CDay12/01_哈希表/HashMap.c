#include "HashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define DEFAULT_CAPACITY 8
#define LOAD_FACTOR   0.75
/*
	创建空的哈希表
*/
HashMap* hashmap_create(void) {
	HashMap* map = malloc(sizeof(HashMap));

	map->table = calloc(DEFAULT_CAPACITY, sizeof(Node*));
	map->size = 0;
	map->capacity = DEFAULT_CAPACITY;
	map->hashseed = time(NULL);

	return map;
}

void hashmap_destroy(HashMap* map) {
    // 1. 释放所有的结点 (遍历哈希表)
    for (int i = 0; i < map->capacity; i++) {
        Node* curr = map->table[i];
        while (curr) {
            Node* next = curr->next;
            free(curr);
            curr = next;
        } // curr == NULL
    }
    // 2. 释放动态数组
    free(map->table);
    // 3. 释放HashMap结构体
    free(map);
}

/* murmurhash2 */
uint32_t hash(const void* key, int len, uint32_t seed) {
    const uint32_t m = 0x5bd1e995;
    const int r = 24;
    uint32_t h = seed ^ len;
    const unsigned char* data = (const unsigned char*)key;

    while (len >= 4) {
        uint32_t k = *(uint32_t*)data;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch (len)
    {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0];
        h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}

/*
	a. 如果key不存在，添加 key-val, 并返回NULL
	b. 如果key存在，更新key关联的val，返回原来的val
*/
V hashmap_put(HashMap* map, K key, V val) {
    int idx = hash(key, strlen(key), map->hashseed) % map->capacity;
    // 遍历链表
    Node* curr = map->table[idx];
    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            // b. 更新key关联的值，并返回原来的值
            V oldval = curr->val;
            curr->val = val;
            return oldval;
        }
        curr = curr->next;
    } // curr == NULL
    // a. 添加 key-val, 并返回NULL
    
    Node* newnode = malloc(sizeof(Node));
    
    newnode->key = key;
    newnode->val = val;
    newnode->next = map->table[idx];
    // 链接
    map->table[idx] = newnode;
    // 更新哈希表的信息
    map->size++;

    return NULL;
}

/*
    根据 key, 获取关联的值；如果key不存在，返回NULL
*/
V hashmap_get(HashMap* map, K key) {
    // 对 key 进行哈希，判断key在哪个哈希桶中
    int idx = hash(key, strlen(key), map->hashseed) % map->capacity;
    // 遍历链表
    Node* curr = map->table[idx];
    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            return curr->val;
        }
        curr = curr->next;
    }   // curr == NULL
    return NULL;
}

/*
    删除键值对；如果key不存在，什么也不做。
*/
void hashmap_delete(HashMap* map, K key) {
    // 对 key 进行哈希，判断key在哪个哈希桶中
    int idx = hash(key, strlen(key), map->hashseed) % map->capacity;
    // 遍历链表
    Node* prev = NULL;
    Node* curr = map->table[idx];
    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            //删除curr结点
            if (prev == NULL) {
                map->table[idx] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            map->size--;
            return;
        }
        prev = curr;
        curr = curr->next;
    } // curr == NULL
}