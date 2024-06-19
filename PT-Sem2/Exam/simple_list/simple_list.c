#include "simple_list.h"
#include <stdlib.h>
#include <stdio.h>

// Usefull functions

void throw_error(const char* msg) {
    perror(msg);
    exit(1);
}

void* safe_alloc(unsigned num_bytes) {
    void *memory = malloc(num_bytes);
    if(memory == NULL) {
        throw_error("Error while using safe alloc");
    }
    return memory;
}

// Main functions

LIST new_list() {
    return (LIST){NULL, NULL};
}

NODE* create_node(INFO info) {
    NODE *node = safe_alloc(sizeof(NODE));
    node->info = info;
    node->next = NULL;
    return node;
}

LIST add_new_node(LIST list, INFO info) {
    NODE *node = create_node(info);

    if(list.head == NULL) {
        list.head = node;
        list.tail = node;
    } else {
        list.tail->next = node;
        list.tail = node;
    }

    return list;
}

LIST add_circular_new_node(LIST list, INFO info) {
    list = add_new_node(list, info);
    list.tail->next = list.head;
    return list;
}

LIST add_sorted_new_node(LIST list, INFO info, int (*compare)(INFO, INFO)) {
    if(list.head == NULL) {
        return add_new_node(list, info);
    } else {
        NODE *current = list.head;
        NODE *previous = NULL;

        while(current != NULL && compare(current->info, info) < 0) {
            previous = current;
            current = current->next;
        }

        NODE *node = create_node(info);
        node->next = current;

        if(previous == NULL) {
            list.head = node;
        } else {
            previous->next = node;
            if(current == NULL) {
                list.tail = node;
            }
        }

        return list;
    }
}

void print_list(LIST list, void (*print_info)(INFO)) {
    NODE *current = list.head;
    printf("List contents: ");

    // Print elements till tail so we can use it for circular lists
    while(current != list.tail) {
        print_info(current->info); printf(" ");
        current = current->next;
    }

    // Print tail element
    print_info(current->info);

    printf("\n");
}

LIST dealloc_list(LIST list) {
    NODE *current = list.head;
    while(current != list.tail) {
        NODE *next = current->next;
        free(current);
        current = next;
    }
    free(list.tail);

    list.head = list.tail = NULL;
    return list;
}