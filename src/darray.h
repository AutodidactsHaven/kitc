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
typedef struct darray {
  // @brief current number of items in the array
  size_t len;
  // @brief total number of items that can fit in the currently allocated memory
  size_t capacity;
  // @brief size of each item in bytes
  size_t type_size;
  // @brief storage
  void* data;

} darray;

/**
 * @brief create a new dynamic array. this function allocates memory for the backing
 *        array as well as for the struct itself
 * @param type_size The size in bytes of the data type being stored in the array (must be homogenous)
 * @param starting_capacity The starting size of the array in terms of number of items
 * @returns A pointer to the darray struct
*/
darray* darray_new(size_t type_size, size_t starting_capacity);

void darray_free(darray *d);

void* darray_resize(darray *d, size_t capacity);

void darray_push(darray *d, const void *value);

/**
 * @brief Pops the last item in the array and places it into dest
*/
void darray_pop(darray *d, void *dest);

/* TODO
 *
 * Public API
 *
 * darray_pop
 * darray_ins(ert)
 * darray_clear
 * darray_len
 *
 * Private API
 * darray_resize
 */

#endif // KITC_DARRAY_H
