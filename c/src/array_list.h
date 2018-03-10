#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct arraylist {
    int n;
    int list_size;
    int* list; 
} arraylist;

arraylist* array_list_init_empty();
arraylist* array_list_init(const int* list, int n);
void array_list_add(arraylist* arr, int element);
void array_list_add_at(arraylist* arr, int element, int index);
int array_list_index_of(arraylist* arr, int element);
void array_list_remove(arraylist* arr, int element);
void array_list_remove_at(arraylist* arr, int index);
bool array_list_contains(arraylist* arr, int element);
bool array_list_is_empty(arraylist* arr);
int array_list_size();
int array_list_get(arraylist* arr, int index);
void array_list_set(arraylist* arr, int index, int element);
void array_list_delete(arraylist* arr);
#endif
