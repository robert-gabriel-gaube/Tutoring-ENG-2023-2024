/*
    Create a doubly linked list with a integer as information in each node.
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int information;
    struct node *after, *before;
}NODE;

typedef struct list {
    NODE *head, *tail;
}LIST;

LIST new_list() {
    LIST list;
    list.head = list.tail = NULL;
    return list;
}

NODE* create_node(int number) { 
    NODE *node = malloc(sizeof(NODE));
    if(node == NULL) {
        printf("Error allocating node\n");
        exit(1);
    }

    node->after = node->before = NULL;
    node->information = number;

    return node;
}

LIST add_new_node(LIST list, int number) {
    if(list.head == NULL) { // The list is empty
        list.head = list.tail = create_node(number);
    } else {
        NODE *node = create_node(number);
        node->before = list.tail;
        list.tail->after = node;

        list.tail = node;

        // // In case of circular doubly linked list
        // list.tail->after = list.head;
        // list.head->before = list.tail;
    }
    return list;
}

void print_list(LIST list) {
    NODE *current = list.head;

    printf("List contents: ");
    while(current != NULL) {
        printf("%d ", current->information);
        current = current -> after;
    }
    printf("\n");
}

void print_reverse_order(LIST list) {
    NODE *current = list.tail;

    printf("List contents: ");
    while(current != NULL) {
        printf("%d ", current->information);
        current = current -> before;
    }
    printf("\n");
}

LIST dealloc_list(LIST list) {
    NODE *current = list.head;

    while(current != NULL) {
        NODE *next = current->after;
        free(current);
        current = next;
    }

    list.head = list.tail = NULL;
    return list;
}

int main() {
    LIST list = new_list();
    
    list = add_new_node(list, 2);
    list = add_new_node(list, 3);
    list = add_new_node(list, 4);
    list = add_new_node(list, 5);

    print_list(list);
    print_reverse_order(list);

    list = dealloc_list(list);
    return 0;
}