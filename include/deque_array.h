/**
 *  bicola (double-ended queue) usando arreglos
 */

 #pragma once
 #include <stdbool.h>
 
 #define MAX_DEQUE_SIZE 100
 
 typedef struct {
     int items[MAX_DEQUE_SIZE];
     int front;
     int rear;
     int size;
 } Deque;
 
 Deque* deque_create();
 void deque_destroy(Deque* deque);
 bool deque_push_front(Deque* deque, int item);
 bool deque_push_back(Deque* deque, int item);
 bool deque_pop_front(Deque* deque, int* out);
 bool deque_pop_back(Deque* deque, int* out);
 bool deque_is_empty(const Deque* deque);
 bool deque_is_full(const Deque* deque);
 int deque_size(const Deque* deque);