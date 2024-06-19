#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    unsigned neighbour, cost;
    struct node *next;
}NODE;

typedef struct node_double {
    NODE *head;
    struct node_double *after, *before;
}NODE_DOUBLE;

typedef struct list {
    NODE_DOUBLE *head, *tail;
}LIST;

LIST new_list() {
    LIST list;
    list.head = list.tail = NULL;
    return list;
}

NODE_DOUBLE* create_double_node() { 
    NODE_DOUBLE *node = malloc(sizeof(NODE_DOUBLE));
    if(node == NULL) {
        printf("Error allocating node\n");
        exit(1);
    }

    node->after = node->before = NULL;
    node->head = NULL;
    return node;
}

LIST add_new_node(LIST list, FILE *input, unsigned n) {
    if(list.head == NULL) { // The list is empty
        list.head = list.tail = create_double_node();
    } else {
        NODE_DOUBLE *node = create_double_node();
        node->before = list.tail;
        list.tail->after = node;
        list.tail = node;

        unsigned elem;
        // Add nodes for each line
        for(int i = 0; i < n; ++i) {
            fscanf(input, "%u", &elem);
            if(elem != 0) {
                // Add to simple linked list 
            }
        }
        printf("\n");

        // In case of circular doubly linked list
        list.tail->after = list.head;
        list.head->before = list.tail;
    }
    return list;
}

/*
Key: 3

Rn, vr pb qdph lv Degxo Udkpdql, Lp iurp sdnlvwdql dqg l zloo whdfk brx wrgdb :
                                   F dqg F++ (lp sur dqg wkhvh 2 duh wkh vdph ewz)

Iluvwob wr fuhdwh d grxeoh olqnhg olvw brx kdyh wr lpsohphqw 2 vwuxfwxuhv, frqwdlqlqj wkh
qrgh zlwk suhylrxv dqg qhaw srvlwlrq ri lw.

L zdqw wr pdnh d mrnh derxw wklv surjudpplqj odqjxdjh, exw zh duh idplob iulhqgob dqg
zh fdqw vruub.

Xq vfkhohwh phujh od edu.
Sulpxo oxfux sh fduh lo fhuh hvwh r ehuh, ldu do 2-ohd xq prs.

*/

int main(int argc, char **argv) {
    if(argc != 2) {
        perror("We don't have enough arguments ./program <name_of_file>");
        exit(1);
    }

    FILE *input = fopen(argv[1], "r");
    if(input == NULL) {
        perror("");
        exit(1);
    }
    unsigned n;
    while(fscanf(input, "%u", &n) == 1);
    printf("%u \n", n);

    // Go back to the beggining
    rewind(input);

    LIST list = new_list();
    unsigned elem;
    for(int i = 0; i < n; ++i) {
        list = add_new_node(list, input, n);
    }

    fclose(input);
    return 0;
}