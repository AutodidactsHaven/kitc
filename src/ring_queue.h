#ifndef KITC_RING_QUEUE_H
#define KITC_RING_QUEUE_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief a fixed-size ring queue
*/
typedef struct kitc_ring_queue {
  size_t len;
  size_t capacity;
  size_t type_size;
  void* data;
  bool owns_memory;    
  int32_t head;
  int32_t tail;
} kitc_ring_queue;

/**
  @brief test
*/
kitc_ring_queue* kitc_ring_queue_new(size_t type_size, size_t capacity, void* memory_block);

void kitc_ring_queue_free(kitc_ring_queue *queue);

bool kitc_ring_queue_enqueue(kitc_ring_queue *queue, const void* value);

bool kitc_ring_queue_dequeue(kitc_ring_queue *queue, void* out_value);

bool kitc_ring_queue_peek(const kitc_ring_queue* queue, void* out_value);


#define KITC_NO_PREFIX
#ifdef KITC_NO_PREFIX
typedef kitc_ring_queue ring_queue;

static inline ring_queue ring_queue_new(size_t type_size, size_t capacity, void* memory_block) {
  return (ring_queue)* kitc_ring_queue_new(type_size, capacity, memory_block);
}

#endif

#endif