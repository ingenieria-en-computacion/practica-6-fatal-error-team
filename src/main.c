#include <stdio.h>
#include <stdlib.h>

// Incluir todos los headers
#define LINKED_LIST_IMPLEMENTATION
#include "../include/linkedlist.h"
#include "../include/circular_queue_array.h"
#include "../include/deque_array.h"
#define CIRCULAR_QUEUE_IMPLEMENTATION
#include "../include/circular_queue.h"
#define DEQUE_IMPLEMENTATION
#include "../include/deque.h"

// Funciones auxiliares para imprimir
void print_int(int value) {
    printf("%d", value);
}

void print_char(char value) {
    printf("%c", value);
}

void print_float(float value) {
    printf("%.2f", value);
}

// Funciones de comparación
bool int_compare(int a, int b) {
    return a == b;
}

bool char_compare(char a, char b) {
    return a == b;
}

bool float_compare(float a, float b) {
    return a == b;
}

void separator(const char* title) {
    printf("\n\nPrueba:  %s \n", title);
}

int main() {
    // 1. Probar lista enlazada genérica (int)
    separator("1. Lista Enlazada Genegrica (int)");
    List_int* int_list = list_int_create();
    
    printf("Append 10, 20, 30:\n");
    list_int_append(int_list, 10);
    list_int_append(int_list, 20);
    list_int_append(int_list, 30);
    list_int_print(int_list, print_int);
    
    printf("\nInsertar 15 en la posicion 1:\n");
    list_int_insert(int_list, 15, 1);
    list_int_print(int_list, print_int);
    
    int value;
    list_int_get(int_list, 2, &value);
    printf("\nElemento en la posicion 2: %d\n", value);
    
    printf("Quita en la posicion 1:\n");
    list_int_remove_at(int_list, 1);
    list_int_print(int_list, print_int);
    
    list_int_destroy(int_list);

    // 2. Probar cola circular con arreglos
    separator("2. Cola Circular con Arreglos");
    CircularQueue* cq = circular_queue_create();
    
    printf("Enqueue 1, 2, 3:\n");
    circular_queue_enqueue(cq, 1);
    circular_queue_enqueue(cq, 2);
    circular_queue_enqueue(cq, 3);
    
    printf("Queue size: %d\n", circular_queue_size(cq));
    
    printf("Dequeue elementos:\n");
    while (!circular_queue_is_empty(cq)) {
        int item;
        circular_queue_dequeue(cq, &item);
        printf("%d ", item);
    }
    printf("\n");
    
    circular_queue_destroy(cq);

    // 3. Probar bicola con arreglos
    separator("3. Bicola con Arreglos");
    Deque* dq = deque_create();
    
    printf("Push front 10, despues back 20, despues front 5:\n");
    deque_push_front(dq, 10);
    deque_push_back(dq, 20);
    deque_push_front(dq, 5);
    
    printf("Deque size: %d\n", deque_size(dq));
    
    printf("Pop front and back:\n");
    int front, back;
    deque_pop_front(dq, &front);
    deque_pop_back(dq, &back);
    printf("Front: %d, Back: %d\n", front, back);
    
    deque_destroy(dq);

    // 4. Probar cola circular genérica (char)
    separator("4. Cola Circular Generica (char)");
    CircularQueue_char* char_cq = circular_queue_char_create(5);
    
    printf("Enqueue A, B, C:\n");
    circular_queue_char_enqueue(char_cq, 'A');
    circular_queue_char_enqueue(char_cq, 'B');
    circular_queue_char_enqueue(char_cq, 'C');
    
    printf("Queue size: %d\n", circular_queue_char_size(char_cq));
    
    printf("Dequeue elementos:\n");
    while (!circular_queue_char_is_empty(char_cq)) {
        char item;
        circular_queue_char_dequeue(char_cq, &item);
        printf("%c ", item);
    }
    printf("\n");
    
    circular_queue_char_destroy(char_cq);

    // 5. Probar bicola genérica (float)
    separator("5. Bicola Generica (float)");
    Deque_float* float_dq = deque_float_create(5);
    
    printf("Push front 1.1, luego back 2.2, luego front 0.5:\n");
    deque_float_push_front(float_dq, 1.1f);
    deque_float_push_back(float_dq, 2.2f);
    deque_float_push_front(float_dq, 0.5f);
    
    printf("Deque size: %d\n", deque_float_size(float_dq));
    
    printf("Pop front and back:\n");
    float f_front, f_back;
    deque_float_pop_front(float_dq, &f_front);
    deque_float_pop_back(float_dq, &f_back);
    printf("Front: %.2f, Back: %.2f\n", f_front, f_back);
    
    deque_float_destroy(float_dq);

    // 6. Prueba adicional con lista de caracteres
    separator("6. Lista Enlazada Generica (char)");
    List_char* char_list = list_char_create();
    
    printf("Append 'H', 'o', 'l', 'a':\n");
    list_char_append(char_list, 'H');
    list_char_append(char_list, 'o');
    list_char_append(char_list, 'l');
    list_char_append(char_list, 'a');
    list_char_print(char_list, print_char);
    
    printf("\nRemove 'l':\n");
    list_char_remove(char_list, char_compare, 'l');
    list_char_print(char_list, print_char);
    
    list_char_destroy(char_list);

    return 0;
}