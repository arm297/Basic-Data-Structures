#include "../src/minheap.h"
#include <assert.h>
#include <stdio.h>

void test_minheap_create(){
    minheap_t * heap = create_heap();
    assert(size(heap) == 0);
    assert(is_empty(heap));
    delete_heap(heap);
    printf("test create\n");
}

void test_minheap_peek(){
    minheap_t * heap = create_heap();
    insert(heap, 1);
    assert(peek(heap) == 1);
    assert(size(heap) == 1);
    assert(!is_empty(heap));
    insert(heap, 2);
    assert(peek(heap) == 1);
    assert(size(heap) == 2);
    insert(heap, -1);
    assert(peek(heap) == -1);
    assert(size(heap) == 3);
    delete_heap(heap);
    printf("test peek\n");
}


void test_minheap_pop(){
    minheap_t * heap = create_heap();
    insert(heap, 13);
    insert(heap, -20);
    insert(heap, 0);
    insert(heap, 3);
    insert(heap, -5);
    insert(heap, 11);
    insert(heap, -1);
    assert(size(heap) == 7);
    assert(pop(heap) == -20);
    assert(size(heap) == 6);
    assert(pop(heap) == -5);
    assert(pop(heap) == -1);
    assert(pop(heap) == 0);
    assert(pop(heap) == 3);
    assert(pop(heap) == 11);
    assert(pop(heap) == 13);
    assert(is_empty(heap));
    for (int i = 99; i > 0; i -= 2){
        insert(heap, i);
    }
    for (int i = 98; i >= 0; i -= 2){
        insert(heap, i);
    }
    for (int i = 0; i < 100; ++i){
        assert(pop(heap) == i);
    }
    delete_heap(heap);
    printf("test pop\n");
}

void test_minheap_replace(){
    minheap_t * heap = create_heap();
    insert(heap, 13);
    insert(heap, -2);
    insert(heap, 0);
    assert(replace(heap, -12) == -2);
    assert(peek(heap) == -12);
    assert(size(heap) == 3);
    assert(replace(heap, 22) == -12);
    assert(peek(heap) == 0);
    assert(size(heap) == 3);
    assert(pop(heap) == 0);
    assert(pop(heap) == 13);
    assert(pop(heap) == 22);
    delete_heap(heap); 
    printf("test replace\n");
}

void test_heapify(){
    int list [] = {1, -4, 5, 0, -3, -22, 10 ,55};
    heapify(list, 8);
    assert(list[0] = -22);
    for (int i = 1; i < 8; ++i){
        assert(list[(i - 1)/2] <= list[i]);
    }
    int large_list[100];
    for (int i = 0; i < 100; ++i){
        large_list[i] = 99 - i;
    }
    heapify(large_list, 100);
    assert(large_list[0] == 0);
    for (int i = 1; i < 8; ++i){
        assert(list[(i - 1)/2] < list[i]);
    }
    printf("test heapify\n");
}

void test_heap_merge(){
    minheap_t * heap1 = create_heap();
    minheap_t * heap2 = create_heap();
    for (int i = 0; i < 100; ++i){
        if (i % 2 == 1){
            insert(heap1, i);
        }
        else{
            insert(heap2, i);
        }
    }
    minheap_t * merged_heap = merge(heap1, heap2);
    minheap_t * self_merged_heap = merge(heap1, heap1);
    for (int i = 0; i < 100; ++i){
        assert(pop(merged_heap) == i);
    }
    for (int i = 0; i < 100; i += 2){
        assert(pop(heap2) == i);
    }
    for (int i = 1; i < 100; i += 2){
        assert(pop(heap1) == i);
        assert(pop(self_merged_heap) == i);
        assert(pop(self_merged_heap) == i);
    }
    delete_heap(heap1);
    delete_heap(heap2);
    delete_heap(merged_heap);
    delete_heap(self_merged_heap);
    printf("tested merge\n");

}

void test_heap_meld(){
    minheap_t * heap1 = create_heap();
    minheap_t * heap2 = create_heap();
    for (int i = 0; i < 100; ++i){
        if (i % 2 == 1){
            insert(heap1, i);
        }
        else{
            insert(heap2, i);
        }
    }
    minheap_t * melded_heap = meld(heap1, heap2);
    for (int i = 0; i < 100; ++i){
        assert(pop(melded_heap) == i);
    }
    delete_heap(melded_heap);
    printf("tested meld\n");
}
