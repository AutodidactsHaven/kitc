#include <assert.h>
#include <stdio.h>
#include "../src/darray.h"

int main() {
  darray *d = darray_new(sizeof(double), 10);
  double value = 64.0;
  for (int i = 0; i < 10; i++) {
    darray_push(d, &value);
    value = value + value;
  }
  assert(d->len == 10);

  for (int i = d->len - 1; i >= 0; i--) {
    double value;
    darray_pop(d, &value);
    printf("value at index %d: %f\n", i, ((double *)d->data)[i]);
  }

  assert(d->len == 0);

  return 0;
}
