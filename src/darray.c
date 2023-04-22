#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "darray.h"

#define DARRAY_DEFAULT_CAPACITY 64
#define DARRAY_RESIZE_FACTOR 3

darray* darray_new(size_t type_size, size_t starting_capacity) {
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

void darray_pop(darray *d, void *dest) {
  void *item = d->data + (d->len - 1) * d->type_size;
  d->len -= 1;
  memcpy(dest, item, d->type_size);
}

