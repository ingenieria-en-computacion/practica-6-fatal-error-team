#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// ----------------------------
// Macro para declarar estructuras y prototipos
// ----------------------------
#define DECLARE_LINKED_LIST(TYPE) \
    typedef struct Node_##TYPE { \
        TYPE data; \
        struct Node_##TYPE* next; \
    } Node_##TYPE; \
    \
    Node_##TYPE* node_##TYPE##_create(TYPE data); \
    void node_##TYPE##_destroy(Node_##TYPE* node); \
    \
    typedef struct { \
        Node_##TYPE* head; \
        Node_##TYPE* tail; \
        size_t length; \
    } List_##TYPE; \
    \
    List_##TYPE* list_##TYPE##_create(void); \
    void list_##TYPE##_destroy(List_##TYPE* list); \
    bool list_##TYPE##_insert(List_##TYPE* list, TYPE data, size_t pos); \
    bool list_##TYPE##_append(List_##TYPE* list, TYPE data); \
    bool list_##TYPE##_remove_at(List_##TYPE* list, size_t pos); \
    bool list_##TYPE##_get(const List_##TYPE* list, size_t pos, TYPE* out); \
    size_t list_##TYPE##_length(const List_##TYPE* list); \
    bool list_##TYPE##_is_empty(const List_##TYPE* list); \
    void list_##TYPE##_clear(List_##TYPE* list); \
    void list_##TYPE##_print(const List_##TYPE* list, void (*print_fn)(TYPE)); \
    bool list_##TYPE##_contains(const List_##TYPE* list, bool (*compare_fn)(TYPE, TYPE), TYPE data); \
    bool list_##TYPE##_remove(List_##TYPE* list, bool (*compare_fn)(TYPE, TYPE), TYPE data);

// ----------------------------
// Macro para implementación
// ----------------------------
#define IMPLEMENT_LINKED_LIST(TYPE) \
    Node_##TYPE* node_##TYPE##_create(TYPE data) { \
        Node_##TYPE* new_node = (Node_##TYPE*)malloc(sizeof(Node_##TYPE)); \
        if (!new_node) return NULL; \
        new_node->data = data; \
        new_node->next = NULL; \
        return new_node; \
    } \
    \
    void node_##TYPE##_destroy(Node_##TYPE* node) { \
        free(node); \
    } \
    \
    List_##TYPE* list_##TYPE##_create(void) { \
        List_##TYPE* list = (List_##TYPE*)malloc(sizeof(List_##TYPE)); \
        if (!list) return NULL; \
        list->head = NULL; \
        list->tail = NULL; \
        list->length = 0; \
        return list; \
    } \
    \
    void list_##TYPE##_destroy(List_##TYPE* list) { \
        if (!list) return; \
        list_##TYPE##_clear(list); \
        free(list); \
    } \
    \
    bool list_##TYPE##_insert(List_##TYPE* list, TYPE data, size_t pos) { \
        if (!list || pos > list->length) return false; \
        \
        Node_##TYPE* new_node = node_##TYPE##_create(data); \
        if (!new_node) return false; \
        \
        if (list->length == 0) { \
            list->head = list->tail = new_node; \
        } else if (pos == 0) { \
            new_node->next = list->head; \
            list->head = new_node; \
        } else if (pos == list->length) { \
            list->tail->next = new_node; \
            list->tail = new_node; \
        } else { \
            Node_##TYPE* current = list->head; \
            for (size_t i = 0; i < pos - 1; ++i) { \
                current = current->next; \
            } \
            new_node->next = current->next; \
            current->next = new_node; \
        } \
        \
        list->length++; \
        return true; \
    } \
    \
    bool list_##TYPE##_append(List_##TYPE* list, TYPE data) { \
        return list_##TYPE##_insert(list, data, list->length); \
    } \
    \
    bool list_##TYPE##_remove_at(List_##TYPE* list, size_t pos) { \
        if (!list || pos >= list->length) return false; \
        \
        Node_##TYPE* to_delete = NULL; \
        \
        if (pos == 0) { \
            to_delete = list->head; \
            list->head = list->head->next; \
            if (list->length == 1) { \
                list->tail = NULL; \
            } \
        } else { \
            Node_##TYPE* current = list->head; \
            for (size_t i = 0; i < pos - 1; ++i) { \
                current = current->next; \
            } \
            to_delete = current->next; \
            current->next = to_delete->next; \
            if (pos == list->length - 1) { \
                list->tail = current; \
            } \
        } \
        \
        node_##TYPE##_destroy(to_delete); \
        list->length--; \
        return true; \
    } \
    \
    bool list_##TYPE##_get(const List_##TYPE* list, size_t pos, TYPE* out) { \
        if (!list || !out || pos >= list->length) return false; \
        \
        Node_##TYPE* current = list->head; \
        for (size_t i = 0; i < pos; ++i) { \
            current = current->next; \
        } \
        \
        *out = current->data; \
        return true; \
    } \
    \
    size_t list_##TYPE##_length(const List_##TYPE* list) { \
        return list ? list->length : 0; \
    } \
    \
    bool list_##TYPE##_is_empty(const List_##TYPE* list) { \
        return list ? list->length == 0 : true; \
    } \
    \
    void list_##TYPE##_clear(List_##TYPE* list) { \
        if (!list) return; \
        \
        Node_##TYPE* current = list->head; \
        while (current) { \
            Node_##TYPE* temp = current; \
            current = current->next; \
            node_##TYPE##_destroy(temp); \
        } \
        \
        list->head = NULL; \
        list->tail = NULL; \
        list->length = 0; \
    } \
    \
    void list_##TYPE##_print(const List_##TYPE* list, void (*print_fn)(TYPE)) { \
        if (!list || !print_fn) return; \
        \
        printf("["); \
        Node_##TYPE* current = list->head; \
        while (current) { \
            print_fn(current->data); \
            current = current->next; \
            if (current) printf(", "); \
        } \
        printf("]\n"); \
    } \
    \
    bool list_##TYPE##_contains(const List_##TYPE* list, bool (*compare_fn)(TYPE, TYPE), TYPE data) { \
        if (!list || !compare_fn) return false; \
        \
        Node_##TYPE* current = list->head; \
        while (current) { \
            if (compare_fn(current->data, data)) { \
                return true; \
            } \
            current = current->next; \
        } \
        \
        return false; \
    } \
    \
    bool list_##TYPE##_remove(List_##TYPE* list, bool (*compare_fn)(TYPE, TYPE), TYPE data) { \
        if (!list || !compare_fn) return false; \
        \
        Node_##TYPE* prev = NULL; \
        Node_##TYPE* current = list->head; \
        \
        while (current) { \
            if (compare_fn(current->data, data)) { \
                if (prev) { \
                    prev->next = current->next; \
                    if (!current->next) { \
                        list->tail = prev; \
                    } \
                } else { \
                    list->head = current->next; \
                    if (!list->head) { \
                        list->tail = NULL; \
                    } \
                } \
                \
                node_##TYPE##_destroy(current); \
                list->length--; \
                return true; \
            } \
            \
            prev = current; \
            current = current->next; \
        } \
        \
        return false; \
    }

// ----------------------------
// Declaración para tipos concretos
// ----------------------------
DECLARE_LINKED_LIST(int)
DECLARE_LINKED_LIST(char)
DECLARE_LINKED_LIST(float)

// ----------------------------
// Implementación para tipos concretos
// ----------------------------
#ifdef LINKED_LIST_IMPLEMENTATION
IMPLEMENT_LINKED_LIST(int)
IMPLEMENT_LINKED_LIST(char)
IMPLEMENT_LINKED_LIST(float)
#endif