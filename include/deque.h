/**
 * Implementación genérica de bicola (double-ended queue)
 * Permite crear bicolas para cualquier tipo de dato
 */

 #pragma once
 #include <stdbool.h>
 #include <stdlib.h>
 
 #define DECLARE_DEQUE(TYPE) \
     typedef struct { \
         TYPE* items; \
         int front; \
         int rear; \
         int size; \
         int capacity; \
     } Deque_##TYPE; \
     \
     Deque_##TYPE* deque_##TYPE##_create(int capacity); \
     void deque_##TYPE##_destroy(Deque_##TYPE* deque); \
     bool deque_##TYPE##_push_front(Deque_##TYPE* deque, TYPE item); \
     bool deque_##TYPE##_push_back(Deque_##TYPE* deque, TYPE item); \
     bool deque_##TYPE##_pop_front(Deque_##TYPE* deque, TYPE* out); \
     bool deque_##TYPE##_pop_back(Deque_##TYPE* deque, TYPE* out); \
     bool deque_##TYPE##_is_empty(const Deque_##TYPE* deque); \
     bool deque_##TYPE##_is_full(const Deque_##TYPE* deque); \
     int deque_##TYPE##_size(const Deque_##TYPE* deque);
 
 #define IMPLEMENT_DEQUE(TYPE) \
     Deque_##TYPE* deque_##TYPE##_create(int capacity) { \
         Deque_##TYPE* deque = malloc(sizeof(Deque_##TYPE)); \
         if (!deque) return NULL; \
         deque->items = malloc(sizeof(TYPE) * capacity); \
         if (!deque->items) { \
             free(deque); \
             return NULL; \
         } \
         deque->front = -1; \
         deque->rear = 0; \
         deque->size = 0; \
         deque->capacity = capacity; \
         return deque; \
     } \
     \
     void deque_##TYPE##_destroy(Deque_##TYPE* deque) { \
         if (!deque) return; \
         free(deque->items); \
         free(deque); \
     } \
     \
     bool deque_##TYPE##_push_front(Deque_##TYPE* deque, TYPE item) { \
         if (!deque || deque_##TYPE##_is_full(deque)) return false; \
         \
         if (deque_##TYPE##_is_empty(deque)) { \
             deque->front = deque->rear = 0; \
         } else if (deque->front == 0) { \
             deque->front = deque->capacity - 1; \
         } else { \
             deque->front--; \
         } \
         \
         deque->items[deque->front] = item; \
         deque->size++; \
         return true; \
     } \
     \
     bool deque_##TYPE##_push_back(Deque_##TYPE* deque, TYPE item) { \
         if (!deque || deque_##TYPE##_is_full(deque)) return false; \
         \
         if (deque_##TYPE##_is_empty(deque)) { \
             deque->front = deque->rear = 0; \
         } else if (deque->rear == deque->capacity - 1) { \
             deque->rear = 0; \
         } else { \
             deque->rear++; \
         } \
         \
         deque->items[deque->rear] = item; \
         deque->size++; \
         return true; \
     } \
     \
     bool deque_##TYPE##_pop_front(Deque_##TYPE* deque, TYPE* out) { \
         if (!deque || !out || deque_##TYPE##_is_empty(deque)) return false; \
         \
         *out = deque->items[deque->front]; \
         \
         if (deque->front == deque->rear) { \
             deque->front = -1; \
             deque->rear = -1; \
         } else if (deque->front == deque->capacity - 1) { \
             deque->front = 0; \
         } else { \
             deque->front++; \
         } \
         \
         deque->size--; \
         return true; \
     } \
     \
     bool deque_##TYPE##_pop_back(Deque_##TYPE* deque, TYPE* out) { \
         if (!deque || !out || deque_##TYPE##_is_empty(deque)) return false; \
         \
         *out = deque->items[deque->rear]; \
         \
         if (deque->front == deque->rear) { \
             deque->front = -1; \
             deque->rear = -1; \
         } else if (deque->rear == 0) { \
             deque->rear = deque->capacity - 1; \
         } else { \
             deque->rear--; \
         } \
         \
         deque->size--; \
         return true; \
     } \
     \
     bool deque_##TYPE##_is_empty(const Deque_##TYPE* deque) { \
         return deque ? deque->size == 0 : true; \
     } \
     \
     bool deque_##TYPE##_is_full(const Deque_##TYPE* deque) { \
         return deque ? deque->size == deque->capacity : false; \
     } \
     \
     int deque_##TYPE##_size(const Deque_##TYPE* deque) { \
         return deque ? deque->size : 0; \
     }
 
 // Declaraciones para tipos concretos
 DECLARE_DEQUE(int)
 DECLARE_DEQUE(char)
 DECLARE_DEQUE(float)
 
 #ifdef DEQUE_IMPLEMENTATION
 IMPLEMENT_DEQUE(int)
 IMPLEMENT_DEQUE(char)
 IMPLEMENT_DEQUE(float)
 #endif