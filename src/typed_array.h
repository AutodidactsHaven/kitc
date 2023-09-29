/**
 * @file typed_array.h
 * @date 2023-09-29
 * @brief Type-safe alternative to darray.
 * @copyright Copyright (c) 2023
*/

#ifndef KITC_TYPED_ARRAY_H
#define KITC_TYPED_ARRAY_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "./darray.h"


#define typed_array(T)  \
  struct {              \
    /* @brief current number of items in the array */ \
    size_t len;         \
    size_t capacity;    \
    T *data;            \
  }                     \


#define KITC_DECL_TYPED_ARRAY(T)                            \
  typedef typed_array(T) T##_darray;                        \
                                                            \
  T##_darray* T##_darray_new(size_t starting_capacity) {    \
      T##_darray *d = malloc(sizeof(T##_darray));           \
      T *data = malloc(starting_capacity * sizeof(T));      \
                                                            \
      d->len = 0;                                           \
      d->capacity = starting_capacity;                      \
      d->data = data;                                       \
                                                            \
      return d;                                             \
    }                                                       \
                                                            \
  void T##_darray_free(T##_darray *d) {                     \
    if (d != NULL) {                                        \
      free(d->data);                                        \
      free(d);                                              \
    }                                                       \
  }                                                         \
                                                            \
  T* T##_darray_resize(T##_darray *d, size_t capacity) {    \
    /* resize the internal data block */                    \
    T *new_data = realloc(d->data, sizeof(T) * capacity);   \
    /* TODO: handle OOM error */                            \
                                                            \
    d->capacity = capacity;                                 \
    d->data = new_data;                                     \
    return new_data;                                        \
  }                                                         \
                                                            \
  void T##_darray_push(T##_darray *d, T value) {            \
    if (d->len >= d->capacity) {                            \
      size_t new_capacity =                                 \
          d->capacity > 0 ? d->capacity * DARRAY_RESIZE_FACTOR : DARRAY_DEFAULT_CAPACITY; \
      T *resized = T##_darray_resize(d, new_capacity);      \
    }                                                       \
                                                            \
    d->data[d->len] = value;                                \
    d->len += 1;                                            \
  }                                                         \
                                                            \
  void T##_darray_push_copy(T##_darray *d, const T *value) { \
    if (d->len >= d->capacity) {                            \
      size_t new_capacity =                                 \
          d->capacity > 0 ? d->capacity * DARRAY_RESIZE_FACTOR : DARRAY_DEFAULT_CAPACITY; \
      T *resized = T##_darray_resize(d, new_capacity);      \
    }                                                       \
                                                            \
    T *place = d->data + d->len;                            \
    d->len += 1;                                            \
    memcpy(place, value, sizeof(T));                        \
  }                                                         \
                                                            \
  void T##_darray_pop(T##_darray *d, T *dest) {             \
    T *item = d->data + (d->len - 1);                       \
    d->len -= 1;                                            \
    memcpy(dest, item, sizeof(T));                          \
  }                                                         \
                                                            \
  void T##_darray_ins(T##_darray *d, const T *value, size_t index) { \
    /* check if requires resize */                          \
    if (d->len + 1 > d->capacity) {                         \
      size_t new_capacity =                                 \
          d->capacity > 0 ? d->capacity * DARRAY_RESIZE_FACTOR : DARRAY_DEFAULT_CAPACITY; \
      T *resized = T##_darray_resize(d, new_capacity);      \
    }                                                       \
                                                            \
    /* shift existing data after index */                   \
    T *insert_dest = d->data + index;                       \
    T *shift_dest = insert_dest + 1;                        \
                                                            \
    int num_items = d->len - index;                         \
                                                            \
    d->len += 1;                                            \
    memcpy(shift_dest, insert_dest, num_items * sizeof(T)); \
    memcpy(insert_dest, value, sizeof(T));                  \
  }                                                         \
                                                            \
  void T##_darray_clear(T##_darray *d) {                    \
    d->len = 0;                                             \
    memset(d->data, 0, d->capacity * sizeof(T));            \
  }                                                         \
                                                            \
  size_t T##_darray_len(T##_darray *d) { return d->len; }   \
                                                            \
  void T##_darray_print(T##_darray *d) {                    \
    printf("len: %zu ", d->len);                            \
    printf("capacity: %zu\n", d->capacity);                 \
    for (int i = 0; i < d->len; i++) {                      \
      printf("Index %d holds value %d\n", i, d->data[i]);   \
    }                                                       \
  }                                                         \

#endif // KITC_TYPED_ARRAY_H