#include <stdio.h>
#include "simple_list.h"

void print_info(INFO info) {
    printf("%d", info.i);
}

int compare_info(INFO info1, INFO info2) {
    return info1.i - info2.i;
}

int main() {
    LIST list = new_list();

    list = add_sorted_new_node(list, (INFO){1}, compare_info);
    list = add_sorted_new_node(list, (INFO){3}, compare_info);
    list = add_sorted_new_node(list, (INFO){2}, compare_info);

    print_list(list, print_info);
    list = dealloc_list(list);
    return 0;
}