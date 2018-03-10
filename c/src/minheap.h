#ifndef MINHEAP_H
#define MINHEAP_H

struct min_heap;

typedef struct min_heap minheap_t;

int size(minheap_t * heap);
int is_empty(minheap_t * heap);

minheap_t * create_heap();
void delete_heap(minheap_t * heap);

int peek(minheap_t * heap);
void insert(minheap_t * heap, int element);
int pop(minheap_t * heap);
int replace(minheap_t * heap, int element);

void heapify(int * list, int n);
minheap_t * merge(minheap_t * heap1, minheap_t * heap2);
minheap_t * meld(minheap_t * heap1, minheap_t * heap2);

#endif
