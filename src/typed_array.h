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
  /* test Docs */       \
  struct {              \
    size_t len;         \
    size_t capacity;    \
    T *data;            \
  }                     \


#define KITC_DECL_TYPED_ARRAY(T)                            \
  typedef typed_array(T) T##_darray;                        \
                                                            \
  T##_darray* T##_darray_new(size_t starting_capacity) {    \
      T##_darray *d = malloc(sizeof(T##_darray));           \
      void *data = malloc(starting_capacity * sizeof(T));   \
                                                            \
      d->len = 0;                                           \
      d->capacity = starting_capacity;                      \
      d->data = data;                                       \
                                                            \
      return d;                                             \
    }                                                       \
                                                            \
  void T##_darray_push(T##_darray *d, T value) {            \
    d->data[d->len] = value;                                \
    d->len += 1;                                            \
  }                                                         \
                                                            \
  void T##_darray_push_copy(T##_darray *d, const T *value) { \
    T *place = d->data + d->len;                            \
    d->len += 1;                                            \
    memcpy(place, value, sizeof(T));                        \
  }                                                         \
                                                            \
  void T##_darray_print(T##_darray *d) {                    \
    printf("len: %zu ", d->len);                            \
    printf("capacity: %zu\n", d->capacity);                 \
    for (int i = 0; i < d->len; i++) {                      \
      printf("Index %d holds value %d\n", i, d->data[i]);   \
    }                                                       \
  }                                                         \
                                                            \
  /**                                                       \
   * @brief Pops the last item in the array and places it   \
   *        into `dest` */                                  \
  void T##_darray_pop(T##_darray *d, T *dest) {             \
    T *item = d->data + (d->len - 1);                       \
    d->len -= 1;                                            \
    memcpy(dest, item, sizeof(T));                          \
  }                                                         \

#endif // KITC_TYPED_ARRAY_H