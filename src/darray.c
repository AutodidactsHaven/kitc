#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "darray.h"

#define DARRAY_DEFAULT_CAPACITY 64
#define DARRAY_RESIZE_FACTOR 3

kitc_darray* kitc_darray_new(size_t type_size, size_t starting_capacity) {
  kitc_darray *d = malloc(sizeof(kitc_darray));
  void *data = malloc(starting_capacity * type_size);

  d->len = 0;
  d->capacity = starting_capacity;
  d->type_size = type_size;
  d->data = data;

  return d;
}

void kitc_darray_free(kitc_darray *d) {
  if (d != NULL) {
    free(d->data);
    free(d);
  }
}

void* kitc_darray_resize(kitc_darray *d, size_t capacity) {
  // resize the internal data block
  void *new_data = realloc(d->data, d->type_size * capacity);
  // TODO: error handling

  d->capacity = capacity;
  d->data = new_data;
  return new_data;
}

void kitc_darray_push(kitc_darray *d, const void *value) {
  if (d->len >= d->capacity) {
    size_t new_capacity = d->capacity > 0 ? d->capacity * DARRAY_RESIZE_FACTOR : DARRAY_DEFAULT_CAPACITY;
    void *resized = kitc_darray_resize(d,new_capacity);
  }

  void *place = d->data + d->len * d->type_size;
  d->len += 1;
  memcpy(place, value, d->type_size);
}

void kitc_darray_pop(kitc_darray *d, void *dest) {
  void *item = d->data + (d->len - 1) * d->type_size;
  d->len -= 1;
  memcpy(dest, item, d->type_size);
}

void kitc_darray_ins(kitc_darray *d, const void *value, size_t index) {
  // check if requires resize
  if (index > d->capacity) {
    // TODO
  }

  // shift that stuff
  void *index_ptr = d->data + index * d->type_size;
  void *dest = d->data + (index + 1) * d->type_size;

  int num_items = d->len - index;

  d->len += 1;
  memcpy(dest, index_ptr, num_items * d->type_size);
  memcpy(index_ptr, value, d->type_size);
}

void kitc_darray_clear(kitc_darray *d) {
  d->len = 0;
  memset(d->data, 0, d->capacity * d->type_size);
}

size_t kitc_darray_len(kitc_darray *d) {
  return d->len;
}
