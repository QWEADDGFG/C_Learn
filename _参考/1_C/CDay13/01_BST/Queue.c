#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_CAPACITY 8
#define MAX_PREALLOC 1024

Queue* queue_create(void) {
	Queue* q = calloc(1, sizeof(Queue));
	q->elements = malloc(DEFAULT_CAPACITY * sizeof(E));
	q->capacity = DEFAULT_CAPACITY;
	return q;
}

void queue_destroy(Queue* q) {
	free(q->elements);
	free(q);
}

void grow_capacity(Queue* q) {
	int new_capacity = q->capacity <= MAX_PREALLOC ?
		(q->capacity << 1) : (q->capacity + MAX_PREALLOC);

	E* new_elements = malloc(new_capacity * sizeof(E));

	// 复制元素
	for (int i = 0; i < q->size; i++) {
		new_elements[i] = q->elements[(q->front + i) % q->capacity];
	}

	free(q->elements);
	q->elements = new_elements;
	q->front = 0;
	q->rear = q->size;
	q->capacity = new_capacity;
}

void queue_push(Queue* q, E val) {
	if (q->size == q->capacity) {
		grow_capacity(q);
	}
	q->elements[q->rear] = val;
	q->rear = (q->rear + 1) % q->capacity;
	q->size++;
}

E queue_pop(Queue* q) {
	if (queue_empty(q)) {
		printf("Error: queue is empty\n");
		exit(1);
	}

	E val = q->elements[q->front];
	q->front = (q->front + 1) % q->capacity;
	q->size--;
	return val;
}

E queue_peek(Queue* q) {
	if (queue_empty(q)) {
		printf("Error: queue is empty\n");
		exit(1);
	}

	return q->elements[q->front];
}

bool queue_empty(Queue* q) {
	return q->size == 0;
}