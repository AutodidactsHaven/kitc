#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

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

darray* darray_new(size_t starting_capacity, size_t type_size) {
  darray *d = malloc(sizeof(darray));
  void *data = malloc(starting_capacity * type_size);

  d->len = 0;
  d->capacity = starting_capacity;
  d->type_size = type_size;
  d->data = data;

  return d;
}

void darray_free(darray *d) {
  if (d != NULL) {
    free(d->data);
    free(d);
  }
}

/* TODO
 *
 * Public API
 *
 * darray_push
 * darray_pop
 * darray_ins(ert)
 * darray_clear
 * darray_len
 *
 * Private API
 * darray_resize
 */
