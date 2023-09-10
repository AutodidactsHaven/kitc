#include "hashtable.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* Implementation inspired by the article https://benhoyt.com/writings/hash-table-in-c/ */

struct kitc_ht_entry {
  const char* key; // NULL = slot is empty
  void* value;
};
static const char* hashtable_set_entry(kitc_ht_entry* entries, size_t capacity,
                                      const char* key, void* value, size_t* plength);

kitc_hashtable* kitc_hashtable_new(size_t starting_capacity) {
  kitc_hashtable* table = malloc(sizeof(kitc_hashtable));

  table->len = 0;
  table->capacity = starting_capacity;

  // allocate backing array
  table->entries = calloc(table->capacity, sizeof(kitc_ht_entry));

  return table;
}

void kitc_hashtable_free(kitc_hashtable *ht) {
  if (ht != NULL) {
    free(ht->entries);
    free(ht);
  }
}

static bool hashtable_expand(kitc_hashtable* ht, size_t new_capacity) {

  kitc_ht_entry* new_entries = calloc(new_capacity, sizeof(kitc_ht_entry));

  // move all non-empty entries to the new table
  for (size_t i; i < ht->capacity; i++) {
    kitc_ht_entry entry = ht->entries[i];
    if (entry.key != NULL) {
      hashtable_set_entry(new_entries, entry.key, entry.value);
    }
  }
}

// ----------- Hash function

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

// FNV-1a hash function
// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
static uint64_t hash_key(const char* key) {
  uint64_t hash = FNV_OFFSET;
  for (const char* p = key; *p; p++) {
      hash ^= (uint64_t)(unsigned char)(*p);
      hash *= FNV_PRIME;
  }
  return hash;
}

// -------------------------

void* kitc_hashtable_get(kitc_hashtable* ht, const char* key) {
  uint64_t hash = hash_key(key);
  size_t index = (size_t)(hash & (uint64_t)(ht->capacity - 1));
  // ? note: why does AND cap - 1 do same thing as modulo cap

  // loop until we find an empty slot
  while (ht->entries[index].key != NULL) {
    if (strcmp(key, ht->entries[index].key) == 0) {
      // found key, return value
      return ht->entries[index].value;
    }
    // key wasn't in this slot, move to next (linear probe)
    index++;
    if (index >= ht->capacity) {
      // At end of entries array, wrap around.
      index = 0;
    }
  }
  return NULL;
}

const char* kitc_hashtable_set(kitc_hashtable* ht, const char* key, void* value) {
  assert(value != NULL);

  
}

