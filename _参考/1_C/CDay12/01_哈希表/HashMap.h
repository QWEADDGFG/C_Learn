#include <stdint.h>

// HashMap.h
typedef char* K;
typedef char* V;

typedef struct node {
	K key;
	V val;
	struct node* next;
} Node;

typedef struct {
	Node** table;
	int size;
	int capacity;
	uint32_t hashseed;
} HashMap;

HashMap* hashmap_create(void);
void hashmap_destroy(HashMap* map);

V hashmap_put(HashMap* map, K key, V val);
V hashmap_get(HashMap* map, K key);
void hashmap_delete(HashMap* map, K key);
