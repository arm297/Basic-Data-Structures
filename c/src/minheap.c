#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct min_heap {
    int num_elements;
    int array_size;
    int * array;
} minheap_t;

int size(minheap_t* heap) {
    return heap->num_elements;
}

int is_empty(minheap_t* heap) {
    return heap->num_elements == 0;
}

int peek(minheap_t* heap) {
    if (is_empty(heap)){
        exit(EXIT_FAILURE);    
    }
    return heap->array[0];
}

minheap_t* create_heap(){
    minheap_t* heap = (minheap_t*) malloc(sizeof(minheap_t));
    heap->array = (int*) malloc(sizeof(int));
    heap->num_elements = 0;
    heap->array_size = 1;
    return heap;
}

void delete_heap(minheap_t* heap) {
    free(heap->array);
    free(heap);
}

void bubble_up(minheap_t* heap, int index) {
    if (index >= heap->num_elements) {
        exit(EXIT_FAILURE);
    }
    int parent = (index - 1) / 2;
    while (index != 0 && heap->array[index] < heap->array[parent]) {
        int t = heap->array[index];
        heap->array[index] = heap->array[parent];
        heap->array[parent] = t;
        index = parent;
        parent = (index - 1) / 2;
    }
}

void insert(minheap_t* heap, int element) {
    if (heap->num_elements + 1 > heap->array_size) {
        int* old_array = heap->array;
        heap->array = (int*) malloc(2 * heap->array_size * sizeof(int));
        memcpy(heap->array, old_array, heap->num_elements * sizeof(int));       
        heap->array_size *= 2;
        free(old_array); 
    }
    heap->array[heap->num_elements] = element;
    heap->num_elements++;
    bubble_up(heap, heap->num_elements-1);    
}

void bubble_down(minheap_t * heap, int index) {
    if (index > heap->num_elements) {
        exit(EXIT_FAILURE);
    }
    while(2 * index + 1 < heap->num_elements) {
        int child1 = 2 * index + 1;
        int child2 = 2 * index + 2; 
        int min_child;
        if (child2 < heap->num_elements) {
            min_child = (heap->array[child1] < heap->array[child2]) 
                ? child1 : child2;
        }
        else {
            min_child = child1;
        }
        if (heap->array[index] > heap->array[min_child]) {
            int t = heap->array[index];
            heap->array[index] = heap->array[min_child];
            heap->array[min_child] = t;
            index = min_child;
        }
        else {
            break;
        }
    }
}

int pop(minheap_t * heap) {
    int smallest_element = *(heap->array);
    heap->array[0] = heap->array[heap->num_elements - 1];
    heap->num_elements--;
    bubble_down(heap, 0);
    return smallest_element;
}

int replace(minheap_t * heap, int element) {
    int smallest_element = heap->array[0];
    heap->array[0] = element;
    bubble_down(heap, 0);
    return  smallest_element;
}

void heapify(int * list, int n) {
    minheap_t localheap;
    localheap.array_size = n;
    localheap.num_elements = n;
    localheap.array = list; 
    for (int i = n-1; i >= 0; --i) {
        bubble_down(&localheap, i);
    }
}

minheap_t * merge(minheap_t * heap1, minheap_t * heap2) {
    minheap_t * larger_heap = (heap1->num_elements > heap2->num_elements) ?
                          heap1 : heap2;
    minheap_t * smaller_heap =  (heap1->num_elements <= heap2->num_elements) ?
                          heap1 : heap2;
    int total_num_elements = heap1->num_elements + heap2->num_elements;
    int new_size = (larger_heap->array_size > total_num_elements) ?
                       larger_heap->array_size : 2 * larger_heap->array_size;
    minheap_t * new_heap = (minheap_t *) malloc(sizeof(minheap_t));
    new_heap->array = (int *) malloc(2 * new_size * sizeof(int));
    new_heap->array_size = new_size;
    memcpy(new_heap->array, larger_heap->array, 
               larger_heap->num_elements * sizeof(int));
    memcpy(new_heap->array + larger_heap->num_elements, smaller_heap->array,
            smaller_heap->num_elements * sizeof(int));
    new_heap->num_elements = total_num_elements;
    heapify(new_heap->array, new_heap->num_elements);
    return new_heap; 
}

minheap_t * meld(minheap_t * heap1, minheap_t * heap2) {
    minheap_t * new_heap = merge(heap1, heap2);
    free(heap1->array);
    free(heap1);
    free(heap2->array);
    free(heap2);
    return new_heap;
}
