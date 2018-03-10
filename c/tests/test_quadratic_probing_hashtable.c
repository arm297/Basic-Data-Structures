#include "../src/quadratic_probing_hashtable.h"
#include <assert.h>
#include <stdio.h>

void test_hashtable_create(){
    hashtable_t * table = hashtable_create();
    assert(hashtable_get_size(table) == 2);
    assert(hashtable_get_num_elements(table) == 0);
    assert(hashtable_get_num_inserts(table) == 0);
    hashtable_delete(table);
}

void test_hashtable_put(){
    hashtable_t * table = hashtable_create();
    hashtable_put(table, 1, 1);
    assert(hashtable_get_size(table) == 4);
    assert(hashtable_get_num_elements(table) == 1);
    assert(hashtable_get_num_inserts(table) == 1);
    assert(hashtable_get(table, 1) == 1);
    hashtable_delete(table);
}

void test_hashtable_put_same_key(){
    hashtable_t * table = hashtable_create();
    hashtable_put(table, 1, 3);
    hashtable_put(table, 1, 1);
    hashtable_put(table, 1, 3);
    hashtable_put(table, 1, 22);
    assert(hashtable_get_size(table) == 4);
    assert(hashtable_get_num_elements(table) == 1);
    assert(hashtable_get_num_inserts(table) == 4);
    assert(hashtable_get(table, 1) == 22);
    hashtable_delete(table);
}

void test_hashtable_put_resize(){
    hashtable_t * table = hashtable_create();
    hashtable_put(table, 1, 3);
    hashtable_put(table, 2, 1);
    assert(hashtable_get_size(table) == 8);
    assert(hashtable_get_num_elements(table) == 2);
    assert(hashtable_get_num_inserts(table) == 3);
    assert(hashtable_get(table, 1) == 3);
    assert(hashtable_get(table, 2) == 1);
    hashtable_put(table, 5, 3);
    assert(hashtable_get_size(table) == 8);
    assert(hashtable_get_num_elements(table) == 3);
    assert(hashtable_get_num_inserts(table) == 4);
    hashtable_put(table, 6, 3);
    assert(hashtable_get_size(table) == 16);
    assert(hashtable_get_num_elements(table) == 4);
    assert(hashtable_get_num_inserts(table) == 8);
    assert(hashtable_get(table, 1) == 3);
    assert(hashtable_get(table, 2) == 1);
    assert(hashtable_get(table, 5) == 3);
    assert(hashtable_get(table, 6) == 3);
    hashtable_delete(table);
}

void test_hashtable_remove(){
    hashtable_t * table = hashtable_create();
    hashtable_put(table, 1, 3);
    hashtable_put(table, 2, 1);
    assert(hashtable_get_size(table) == 8);
    assert(hashtable_get_num_elements(table) == 2);
    assert(hashtable_get_num_inserts(table) == 3);
    assert(hashtable_get(table, 1) == 3);
    assert(hashtable_get(table, 2) == 1);
    hashtable_remove(table, 1);
    assert(hashtable_get_num_elements(table) == 1);
    assert(hashtable_get_num_inserts(table) == 3);
    assert(hashtable_get(table, 2) == 1); 
    hashtable_put(table, 5, 3);
    hashtable_put(table, 6, 3);
    hashtable_remove(table, 6);
    assert(hashtable_get_size(table) == 8);
    assert(hashtable_get_num_elements(table) == 2);
    assert(hashtable_get_num_inserts(table) == 5);
    assert(hashtable_get(table, 2) == 1);
    assert(hashtable_get(table, 5) == 3);
    hashtable_delete(table);
}
