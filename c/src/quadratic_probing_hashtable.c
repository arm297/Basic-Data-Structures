//Integer hash table probing practice problem
#include "quadratic_probing_hashtable.h"

#include <stdio.h>
#include <stdlib.h>

int hashtable_get_size(hashtable_t* table) {
    return table->size;
}

int hashtable_get_num_elements(hashtable_t* table) {
    return table->num_elements;
}

int hashtable_get_num_inserts(hashtable_t* table) {
    return table->num_inserts;
}

hashtable_t * hashtable_create() {
    hashtable_t * table = (hashtable_t*) malloc(sizeof(hashtable_t));
    table->array= (struct bucket**) calloc(INITIAL_CAPACITY, sizeof(struct bucket*));
    table->size = INITIAL_CAPACITY;
    table->num_elements = 0;
    table->num_inserts = 0;
    return table;
}

void hashtable_delete(hashtable_t * table) {
    for (int i = 0; i < table->size; ++i) {
        if (table->array[i]) {
            free(table->array[i]);
        }
    }
    table->size = 0;
    table->num_inserts = 0;
    table->num_elements = 0;
    free(table->array);
    free(table);
}

// Credits given to Stack Overflow
// link: https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
unsigned int hash(unsigned int x){
     x = ((x >> 16) ^ x) * 0x45d9f3b;
     x = ((x >> 16) ^ x) * 0x45d9f3b;
     x = (x >> 16) ^ x;
     return x;
}

int hashtable_get(hashtable_t * table, int key) {
    int hash_val = hash((unsigned int) key) % table->size;
    for (int i = 0; i <= table->size; ++i) {
        int hashed_index = (hash_val + i*i) % table->size;
        struct bucket * indexed_bucket = table->array[hashed_index];
        if (indexed_bucket && indexed_bucket->valid 
                && indexed_bucket->key == key) {
            return indexed_bucket->value;
        }
    }
    exit(-1);
}

void hashtable_remove(hashtable_t * table, int key) {
    int hash_val = hash((unsigned int) key) % table->size;
    for (int i = 0; i <= table->size; ++i) {
        int hashed_index = (hash_val + i*i) % table->size;
        struct bucket* indexed_bucket = table->array[hashed_index];
        if (indexed_bucket && indexed_bucket->valid
                && indexed_bucket->key == key) {
            indexed_bucket->valid = 0;
            table->num_elements -= 1;
            return;
        }
    }
    exit(-1);
}

int quadratic_probe(hashtable_t * table, int key) {
    int hash_val = hash((unsigned int) key) % table->size;
    for (int i = 0; i <= table->size; ++i) {
        int hashed_index = (hash_val + i*i) % table->size;
        struct bucket* indexed_bucket = table->array[hashed_index];
        if (!indexed_bucket || !indexed_bucket->valid
            || indexed_bucket->key == key) {
            return hashed_index;
        }
    }
    exit(-1);
}

void resize(hashtable_t * table) {
    struct bucket ** old_array = table->array;
    int old_size = table->size;
    table->array = (struct bucket**) calloc(2 * table->size,
                                            sizeof(struct bucket*));
    table->size *= 2;
    for (int i = 0; i < old_size; ++i) {
        struct bucket * indexed_bucket = old_array[i];
        if (indexed_bucket) {
            if (indexed_bucket ->valid) {
                int new_index = quadratic_probe(table, indexed_bucket->key);
                *(table->array + new_index) = indexed_bucket;
                table->num_inserts++;
            }
            else {
                free(indexed_bucket);
            }
        }
    }
    free(old_array);
}

void hashtable_put(hashtable_t * table, int key, int value) {
    int probed_index = quadratic_probe(table, key);
    struct bucket* probed_bucket = table->array[probed_index];
    if (probed_bucket) {
        probed_bucket->key = key;
        probed_bucket->value = value;
        if (!probed_bucket->valid) {
            table->num_elements++;
            probed_bucket->valid = 1;
        }
    }
    else{
        struct bucket* new_bucket = (struct bucket*) malloc(sizeof(struct bucket));
        new_bucket->key = key;
        new_bucket->value = value;
        new_bucket->valid = 1;
        table->array[probed_index] = new_bucket;
        table->num_elements++;
    }
    if (((float)table->num_elements / table->size) >= 0.5) {
        resize(table);
    }
    else{
        table->num_inserts++;
    }
}

void hashtable_stats(hashtable_t * table){
    printf("length = %d, N = %d, puts = %d\n", table->size,
           table->num_elements, table->num_inserts);
}
