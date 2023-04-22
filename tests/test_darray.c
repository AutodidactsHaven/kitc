#include <assert.h>
#include <stdio.h>
#include "../src/darray.h"

int main() {
  kitc_darray *d = kitc_darray_new(sizeof(double), 11);
  double value = 64.0;
  for (int i = 0; i < 10; i++) {
    kitc_darray_push(d, &value);
    value = value + value;
  }
  assert(d->len == 10);

  double inserted_value = 11111111.0;
  kitc_darray_ins(d, &inserted_value, 4);

  for (int i = d->len - 1; i >= 0; i--) {
    double value;
    kitc_darray_pop(d, &value);
    printf("value at index %d: %f\n", i, ((double *)d->data)[i]);
  }

  assert(d->len == 0);

  return 0;
}
