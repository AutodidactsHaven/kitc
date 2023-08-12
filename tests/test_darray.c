#include <assert.h>
#include <stdio.h>
#include "../src/darray.h"

int main() {
  // Basic push example
  kitc_darray *d = kitc_darray_new(sizeof(double), 11);
  double value = 64.0;
  for (int i = 0; i < 10; i++) {
    kitc_darray_push(d, &value);
    value = value + value;
  }
  assert(d->len == 10);

  double inserted_value = 11111111.0;
  kitc_darray_ins(d, &inserted_value, 4);

  // Demonstrate pulling data out with an explicit cast and popping elements
  for (int i = d->len - 1; i >= 0; i--) {
    double value;
    kitc_darray_pop(d, &value);
    printf("value at index %d: %f\n", i, ((double *)d->data)[i]);
  }

  assert(d->len == 0);

  // Iterator example
  // ================
  
  // push some values back in
  double new_value = 1.0;
  for (int i = 0; i < 10; i++) {
    kitc_darray_push(d, &new_value);
    new_value++;
  }

  // create iterator and print out all values
  kitc_darray_iter double_iter = kitc_darray_iter_new(d);
  double *current;
  while ((current = kitc_darray_iter_next(&double_iter))) {
    printf("value %.2f\n", *current);
  }

  return 0;
}
