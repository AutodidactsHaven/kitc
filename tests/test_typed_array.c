#include <assert.h>
#include <stdio.h>
#include <stdint.h>

#include "../src/typed_array.h"

typedef int32_t i32;
KITC_DECL_TYPED_ARRAY(i32) // this is how we declare a new array type

int main() {
  i32_darray *ints = i32_darray_new(64); // starting capacity of 64

  // Basic push example
  i32 value = 5;
  for (int i = 0; i < 5; i++) {
    i32_darray_push(ints, value);
    value = value + 5;
  }

  i32_darray_print(ints);

  i32 last_value;
  i32_darray_pop(ints, &last_value);
  printf("The last value was %d\nThe new len is %zu\n", last_value, ints->len);
  
  return 0;
}

struct dummy_struct {
  // we can store them in structs with a better name now too
  i32_darray my_ints_vec;
};