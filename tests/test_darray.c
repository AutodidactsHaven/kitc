#include <stdio.h>
#include "../src/darray.h"

int main() {
  darray *d = darray_new(600, sizeof(double));
  double value = 64.0;
  darray_push(d, &value);

  for (int i = 0; i < d->len; ++i) {
    printf("value: %f\n", ((double*)d->data)[i]);
  }

  return 0;
}
