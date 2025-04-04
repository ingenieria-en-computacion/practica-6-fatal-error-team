#include "deque_array.h"
#include <stdlib.h>
Deque* deque_create() {
    Deque* deque = (Deque*)malloc(sizeof(Deque));
    if (!deque) return NULL;
    
    deque->front = -1;
    deque->rear = 0;
    deque->size = 0;
    return deque;
}

void deque_destroy(Deque* deque) {
    if (deque) free(deque);
}

bool deque_push_front(Deque* deque, int item) {
    if (deque_is_full(deque)) return false;
    
    if (deque_is_empty(deque)) {
        deque->front = deque->rear = 0;
    } else if (deque->front == 0) {
        deque->front = MAX_DEQUE_SIZE - 1;
    } else {
        deque->front--;
    }
    
    deque->items[deque->front] = item;
    deque->size++;
    return true;
}

bool deque_push_back(Deque* deque, int item) {
    if (deque_is_full(deque)) return false;
    
    if (deque_is_empty(deque)) {
        deque->front = deque->rear = 0;
    } else if (deque->rear == MAX_DEQUE_SIZE - 1) {
        deque->rear = 0;
    } else {
        deque->rear++;
    }
    
    deque->items[deque->rear] = item;
    deque->size++;
    return true;
}

bool deque_pop_front(Deque* deque, int* out) {
    if (deque_is_empty(deque) || !out) return false;
    
    *out = deque->items[deque->front];
    if (deque->front == deque->rear) {
        deque->front = -1;
        deque->rear = -1;
    } else if (deque->front == MAX_DEQUE_SIZE - 1) {
        deque->front = 0;
    } else {
        deque->front++;
    }
    
    deque->size--;
    return true;
}

bool deque_pop_back(Deque* deque, int* out) {
    if (deque_is_empty(deque) || !out) return false;
    
    *out = deque->items[deque->rear];
    if (deque->front == deque->rear) {
        deque->front = -1;
        deque->rear = -1;
    } else if (deque->rear == 0) {
        deque->rear = MAX_DEQUE_SIZE - 1;
    } else {
        deque->rear--;
    }
    
    deque->size--;
    return true;
}

bool deque_is_empty(const Deque* deque) {
    return deque ? deque->size == 0 : true;
}

bool deque_is_full(const Deque* deque) {
    return deque ? deque->size == MAX_DEQUE_SIZE : false;
}

int deque_size(const Deque* deque) {
    return deque ? deque->size : 0;
}