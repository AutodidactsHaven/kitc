// Simple hash table with linear probing for handling collisions
// TODO: extend to handle non char* keys

#ifndef KITC_HASHTABLE_H
#define KITC_HASHTABLE_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

// starting off with a string hashtable only

typedef struct kitc_ht_entry kitc_ht_entry;

typedef struct kitc_hashtable {
  size_t len;
  size_t capacity;
  kitc_ht_entry* entries;
} kitc_hashtable;

/**
 * @brief create a new hash table. this function does not allocate any memory on the heap.
          once you insert the first item it will allocate the backing array
*/
kitc_hashtable* kitc_hashtable_new(size_t starting_capacity);

void kitc_hashtable_free(kitc_hashtable* ht);

/**
 * @brief get item with the given key
*/
void* kitc_hashtable_get(kitc_hashtable* ht, const char* key);

/**
 * @brief set item for the given key
*/
const char* kitc_hashtable_set(kitc_hashtable* ht, const char* key, void* value);

size_t kitc_hashtable_len(const kitc_hashtable* ht);

// TODO: iterator

#endif