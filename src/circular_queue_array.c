#include "circular_queue_array.h"
#include <stdlib.h>
CircularQueue* circular_queue_create() {
    CircularQueue* queue = (CircularQueue*)malloc(sizeof(CircularQueue));
    if (!queue) return NULL;
    
    queue->front = -1;
    queue->rear = -1;
    queue->size = 0;
    return queue;
}

void circular_queue_destroy(CircularQueue* queue) {
    if (queue) free(queue);
}

bool circular_queue_enqueue(CircularQueue* queue, int item) {
    if (circular_queue_is_full(queue)) return false;
    
    if (circular_queue_is_empty(queue)) {
        queue->front = 0;
    }
    queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
    queue->items[queue->rear] = item;
    queue->size++;
    return true;
}

bool circular_queue_dequeue(CircularQueue* queue, int* out) {
    if (circular_queue_is_empty(queue) || !out) return false;
    
    *out = queue->items[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
    }
    queue->size--;
    return true;
}

bool circular_queue_is_empty(const CircularQueue* queue) {
    return queue ? queue->size == 0 : true;
}

bool circular_queue_is_full(const CircularQueue* queue) {
    return queue ? queue->size == MAX_QUEUE_SIZE : false;
}

int circular_queue_size(const CircularQueue* queue) {
    return queue ? queue->size : 0;
}