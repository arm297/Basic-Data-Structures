#ifndef QUADRATIC_PROBING_HASHTABLE_H
#define QUADRATIC_PROBING_HASHTABLE_H
#define INITIAL_CAPACITY 2

struct hash_table;

//Hash table structure type
typedef struct hash_table hashtable_t;

//Returns the size of table
int hashtable_get_size(hashtable_t * table);

//Returns the number of elements in table
int hashtable_get_num_elements(hashtable_t * table);

//Returns the number of inserts which table has done
int hashtable_get_num_inserts(hashtable_t * table);

//Creates a new hash table
hashtable_t * hashtable_create();

//Deletes table
void hashtable_delete(hashtable_t * table);

//Gets the value indexed by key in the table
int hashtable_get(hashtable_t * table, int key);

//Removes the value indexed by key in the table
void hashtable_remove(hashtable_t * table, int key);

//Puts the key value pair in the table
void hashtable_put(hashtable_t * table, int key, int value);

//Prints the stats for table
void hashtable_stats(hashtable_t * table);

#endif
