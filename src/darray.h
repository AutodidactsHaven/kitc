#ifndef KITC_DARRAY_H
#define KITC_DARRAY_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#define DARRAY_DEFAULT_CAPACITY 64
#define DARRAY_RESIZE_FACTOR 3

/// Dynamic array (think C++/Rust's vector/Vec)
/// resizes memory internally when length exceeds the capacity
typedef struct kitc_darray {
  // @brief current number of items in the array
  size_t len;
  // @brief total number of items that can fit in the currently allocated memory
  size_t capacity;
  // @brief size of each item in bytes
  size_t type_size;
  // @brief storage
  void* data;

} kitc_darray;

/**
 * @brief create a new dynamic array. this function allocates memory for the backing
 *        array as well as for the struct itself
 * @param type_size The size in bytes of the data type being stored in the array (must be homogenous)
 * @param starting_capacity The starting size of the array in terms of number of items
 * @returns A pointer to the kitc_darray struct
*/
kitc_darray* kitc_darray_new(size_t type_size, size_t starting_capacity);

void kitc_darray_free(kitc_darray *d);

void* kitc_darray_resize(kitc_darray *d, size_t capacity);

void kitc_darray_push(kitc_darray *d, const void *value);

/**
 * @brief Pops the last item in the array and places it into dest
*/
void kitc_darray_pop(kitc_darray *d, void *dest);

/**
 * @brief Insert a value at a given index
 * @note O(n) because it has to shift all items to the right of index
*/
void kitc_darray_ins(kitc_darray *d, const void *value, size_t index);

/**
 * @brief clear array by resetting all memory to 0
*/
void kitc_darray_clear(kitc_darray *d);

/**
 * @returns number of items currently in the array
*/
size_t kitc_darray_len(kitc_darray *d);

/**
  @brief an iterator that can be used to iterate through the array more easily
          than using for loops with variables
*/
typedef struct kitc_darray_iter {
  kitc_darray *array;
  size_t current_idx;
} kitc_darray_iter;

/**
 * @brief creates a support iterator struct
 * @returns the iterator struct. pass this to `kitc_darray_iter_next`
*/
kitc_darray_iter kitc_darray_iter_new(kitc_darray *d);

/**
 * @returns a pointer to the next element in the array or NULL if you're at the end
*/
void* kitc_darray_iter_next(kitc_darray_iter *iterator);

// TODO: decide more functions for public API

#endif // KITC_DARRAY_H
