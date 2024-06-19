#ifndef __SIMPLE_LIST_H__
#define __SIMPLE_LIST_H__

typedef struct {
    int i;
}INFO;

typedef struct node {
    INFO info;
    struct node *next;
}NODE;

typedef struct {
    NODE *head;
    NODE *tail;
}LIST;

LIST new_list();

LIST add_new_node(LIST list, INFO info);
LIST add_circular_new_node(LIST list, INFO info);
LIST add_sorted_new_node(LIST list, INFO info, int (*compare)(INFO, INFO));

void print_list(LIST list, void (*print_info)(INFO));
LIST dealloc_list(LIST list);

#endif /* __SIMPLE_LIST_H__ */