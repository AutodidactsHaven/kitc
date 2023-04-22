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

void* darray_resize(darray *d, size_t capacity) {
  // resize the internal data block
  void *new_data = realloc(d->data, d->type_size * capacity);
  // TODO: error handling

  d->capacity = capacity;
  d->data = new_data;
  return new_data;
}

void darray_push(darray *d, const void *value) {
  if (d->len >= d->capacity) {
    size_t new_capacity = d->capacity > 0 ? d->capacity * DARRAY_RESIZE_FACTOR : DARRAY_DEFAULT_CAPACITY;
    void *resized = darray_resize(d,new_capacity);
  }

  void *place = d->data + d->len * d->type_size;
  d->len += 1;
  memcpy(place, value, d->type_size);
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
