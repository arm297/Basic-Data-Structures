#include "test_minheap.h"
#include "test_quadratic_probing_hashtable.h"

void test_minheap(){
    test_minheap_create();
    test_minheap_peek();
    test_minheap_pop();
    test_minheap_replace();
    test_heapify();
    test_heap_merge();
    test_heap_meld();
}

void test_quadratic_probing_hashtable(){
    test_hashtable_create();
    test_hashtable_put();
    test_hashtable_put_same_key();
    test_hashtable_put_resize();
    test_hashtable_remove();
}

int main(){
    test_minheap();
    test_quadratic_probing_hashtable();
}
