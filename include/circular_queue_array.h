/**
 * Implementación de cola circular usando arreglos y valores enteros
 */

 #pragma once
 #include <stdbool.h>
 
 #define MAX_QUEUE_SIZE 100
 
 typedef struct {
     int items[MAX_QUEUE_SIZE];
     int front;
     int rear;
     int size;
 } CircularQueue;
 
 CircularQueue* circular_queue_create();
 void circular_queue_destroy(CircularQueue* queue);
 bool circular_queue_enqueue(CircularQueue* queue, int item);
 bool circular_queue_dequeue(CircularQueue* queue, int* out);
 bool circular_queue_is_empty(const CircularQueue* queue);
 bool circular_queue_is_full(const CircularQueue* queue);
 int circular_queue_size(const CircularQueue* queue);