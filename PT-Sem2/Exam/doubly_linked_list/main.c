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

LIST add_new_node(LIST list, int number, int (*compare)(int, int)) {
    if(list.head == NULL) { // The list is empty
        list.head = list.tail = create_node(number);
    } else {
        NODE *node = create_node(number);
        NODE *current = list.head;

        // Find the position of insertion
        while(current != NULL && compare(current->information, number) < 0) {
            current = current -> after;
        }

        if(current == list.head) { // If we add to the front
            node->after = list.head;
            list.head->before = node;
            list.head = node;
        } else if(current == NULL) { // If we add to the end
            list.tail->after = node;
            node->before = list.tail;
            list.tail = node;
        } else {
            node->before = current->before;
            node->after = current;
            current->before->after = node;
            current->before = node;
        }

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

int compare(int a, int b) {
    return a - b;
}

int main() {
    LIST list = new_list();
    
    list = add_new_node(list, 3, compare);
    list = add_new_node(list, 2, compare);
    list = add_new_node(list, 5, compare);
    list = add_new_node(list, 4, compare);

    print_list(list);
    print_reverse_order(list);

    list = dealloc_list(list);
    return 0;
}