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

darray* darray_new(size_t starting_capacity, size_t type_size);

void darray_free(darray *d);

void* darray_resize(darray *d, size_t capacity);

void darray_push(darray *d, const void *value);
