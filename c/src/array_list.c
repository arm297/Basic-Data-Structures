#include "array_list.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


arraylist* array_list_init_empty() {
    arraylist* arr = (arraylist*) malloc(sizeof(arraylist));
    arr->n = 0;
    arr->list_size = 2;
    arr->list = (int*)malloc(arr->list_size * sizeof(int));
    return arr;
}

arraylist* array_list_init(const int* list, int n) {
    arraylist* arr = (arraylist*) malloc(sizeof(arraylist));
    arr->n = n;
    arr->list_size = (n > 2) ? n : 2;
    arr->list = (int*)malloc(arr->list_size * sizeof(int));
    memcpy(arr->list, list, n * sizeof(int));
    return arr;
}

static inline void resize(arraylist* arr) {
    arr->list_size *= 2;
    arr->list = (int*)realloc(arr->list, arr->list_size * sizeof(int));
}

void array_list_add(arraylist* arr, int element) {
    if (arr->list_size == arr->n + 1) {
        resize(arr);
    }
    arr->list[arr->n] = element;
    arr->n++;
}

void array_list_add_at(arraylist* arr, int element, int index) {
    if (arr->list_size == arr->n + 1) {
        resize(arr);
    }
    memcpy(arr->list + index + 1, arr->list + index, 
            (arr->n - index) * sizeof(int));
    arr->list[index] = element;
    arr->n++;
}

int array_list_index_of(arraylist* arr, int element) {
    if (!element) {
        return -1;
    }
    for (int i = 0; i < arr->n; i++) {
        if (arr->list[i] == element) {
            return i;
        }
    }
    return -1;
}

void array_list_remove(arraylist* arr, int element) {
    int at = array_list_index_of(arr, element);
    if (at == -1) {
        return;
    }
    memcpy(arr->list + at, arr->list + at + 1, (arr->n - at - 1) *
            sizeof(int));
    arr->n--;
}

void array_list_remove_at(arraylist* arr, int index) {
    if (index >= arr->n) {
        return;
    }
    memcpy(arr->list + index, arr->list + index + 1, (arr->n - index - 1) *
            sizeof(int));
    arr->n--;
}

bool array_list_contains(arraylist* arr, int element) {
    for (int i = 0; i < arr->n; i++) {
        if (arr->list[i] == element) {
            return true;
        }
    }
    return false;
}

bool array_list_is_empty(arraylist* arr) {
    return arr->n == 0;
}

int array_list_size(arraylist* arr) {
    return arr->n;
}

int array_list_get(arraylist* arr, int index) {
    return arr->list[index];
}

void array_list_set(arraylist* arr, int index, int element) {
    if (index <= arr->n) {
        return;
    }
    arr->list[index] = element;
}

void array_list_delete(arraylist* arr) {
    if (arr) {
        free(arr->list);
        free(arr);
    }
}
