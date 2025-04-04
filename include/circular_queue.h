/**
 *  cola circular generica (Permite crear colas circulares para cualquier tipo de dato)
 */

 #pragma once
 #include <stdbool.h>
 #include <stdlib.h>
 
 #define DECLARE_CIRCULAR_QUEUE(TYPE) \
     typedef struct { \
         TYPE* items; \
         int front; \
         int rear; \
         int size; \
         int capacity; \
     } CircularQueue_##TYPE; \
     \
     CircularQueue_##TYPE* circular_queue_##TYPE##_create(int capacity); \
     void circular_queue_##TYPE##_destroy(CircularQueue_##TYPE* queue); \
     bool circular_queue_##TYPE##_enqueue(CircularQueue_##TYPE* queue, TYPE item); \
     bool circular_queue_##TYPE##_dequeue(CircularQueue_##TYPE* queue, TYPE* out); \
     bool circular_queue_##TYPE##_is_empty(const CircularQueue_##TYPE* queue); \
     bool circular_queue_##TYPE##_is_full(const CircularQueue_##TYPE* queue); \
     int circular_queue_##TYPE##_size(const CircularQueue_##TYPE* queue);
 
 #define IMPLEMENT_CIRCULAR_QUEUE(TYPE) \
     CircularQueue_##TYPE* circular_queue_##TYPE##_create(int capacity) { \
         CircularQueue_##TYPE* queue = malloc(sizeof(CircularQueue_##TYPE)); \
         if (!queue) return NULL; \
         queue->items = malloc(sizeof(TYPE) * capacity); \
         if (!queue->items) { \
             free(queue); \
             return NULL; \
         } \
         queue->front = queue->rear = -1; \
         queue->size = 0; \
         queue->capacity = capacity; \
         return queue; \
     } \
     \
     void circular_queue_##TYPE##_destroy(CircularQueue_##TYPE* queue) { \
         if (!queue) return; \
         free(queue->items); \
         free(queue); \
     } \
     \
     bool circular_queue_##TYPE##_enqueue(CircularQueue_##TYPE* queue, TYPE item) { \
         if (!queue || circular_queue_##TYPE##_is_full(queue)) return false; \
         \
         if (circular_queue_##TYPE##_is_empty(queue)) { \
             queue->front = queue->rear = 0; \
         } else { \
             queue->rear = (queue->rear + 1) % queue->capacity; \
         } \
         \
         queue->items[queue->rear] = item; \
         queue->size++; \
         return true; \
     } \
     \
     bool circular_queue_##TYPE##_dequeue(CircularQueue_##TYPE* queue, TYPE* out) { \
         if (!queue || !out || circular_queue_##TYPE##_is_empty(queue)) return false; \
         \
         *out = queue->items[queue->front]; \
         \
         if (queue->front == queue->rear) { \
             queue->front = queue->rear = -1; \
         } else { \
             queue->front = (queue->front + 1) % queue->capacity; \
         } \
         \
         queue->size--; \
         return true; \
     } \
     \
     bool circular_queue_##TYPE##_is_empty(const CircularQueue_##TYPE* queue) { \
         return queue ? queue->size == 0 : true; \
     } \
     \
     bool circular_queue_##TYPE##_is_full(const CircularQueue_##TYPE* queue) { \
         return queue ? queue->size == queue->capacity : false; \
     } \
     \
     int circular_queue_##TYPE##_size(const CircularQueue_##TYPE* queue) { \
         return queue ? queue->size : 0; \
     }
 
 // Declaraciones para tipos concretos
 DECLARE_CIRCULAR_QUEUE(int)
 DECLARE_CIRCULAR_QUEUE(char)
 DECLARE_CIRCULAR_QUEUE(float)
 
 #ifdef CIRCULAR_QUEUE_IMPLEMENTATION
 IMPLEMENT_CIRCULAR_QUEUE(int)
 IMPLEMENT_CIRCULAR_QUEUE(char)
 IMPLEMENT_CIRCULAR_QUEUE(float)
 #endif