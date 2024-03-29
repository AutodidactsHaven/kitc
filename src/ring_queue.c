#include "ring_queue.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

kitc_ring_queue* kitc_ring_queue_new(size_t type_size, size_t capacity, void* memory) {
    kitc_ring_queue *q = malloc(sizeof(kitc_ring_queue));
    q->len = 0;
    q->capacity = capacity;
    q->type_size = type_size;
    q->head = 0;
    q->tail = -1;

    if (memory) {
        // caller owns the memory
        q->owns_memory = false;
        q->data = memory;
    } else {
        // ring queue should own the memory
        q->owns_memory = true;
        q->data = malloc(capacity * type_size);
    }

    return q;
}

void kitc_ring_queue_free(kitc_ring_queue *queue) {
    if (queue) {
        if (queue->owns_memory) {
            free(queue->data);
        }
        free(queue);
    }
}

bool kitc_ring_queue_enqueue(kitc_ring_queue *queue, const void* value) {
    if (queue->len == queue->capacity) {
        return false;
    }

    queue->tail = (queue->tail + 1) % queue->capacity;
    memcpy(queue->data + (queue->tail * queue->type_size), value, queue->type_size);
    queue->len++;
    return true;
}

bool kitc_ring_queue_dequeue(kitc_ring_queue *queue, void* out_value) {
    if (queue->len == 0) {
        // queue is empty
        return false;
    }

    memcpy(out_value, queue->data + (queue->head * queue->type_size), queue->type_size);
    queue->head = (queue->head + 1) % queue->capacity;
    queue->len--;
    return true;
}

bool kitc_ring_queue_peek(const kitc_ring_queue* queue, void* out_value) {
    if (queue->len == 0) {
        // queue is empty
        return false;
    }

    memcpy(out_value, queue->data + (queue->head * queue->type_size), queue->type_size);
    return true;
}