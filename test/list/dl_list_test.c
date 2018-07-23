#include <stdio.h>

#include "list.h"

#define JLIB_LIST_IMPL
#include "list.h"
#undef JLIB_LIST_IMPL

typedef struct node {
    struct list_node list_node;
    int val;
} node_t;

int cmp(void *l, void *r) {
    return ((node_t*)l)->val - ((node_t*)r)->val;
}

void print_list(struct dl_list *list) {
    struct list_node *n = list->head;
    while (n) {
        printf("%d ", ((node_t*)n)->val);
        n = n->next;
    }
    printf("\n");
}

void test_prepend() {
    printf("Testing prepend...\n");

    struct dl_list list;
    dl_list_init(&list);

    node_t a, b, c;
    a.val = 1;
    b.val = 2;
    c.val = 3;
    
    dl_list_prepend(&list, AS_LIST_NODE(&a));
    dl_list_prepend(&list, AS_LIST_NODE(&b));
    dl_list_prepend(&list, AS_LIST_NODE(&c));
    print_list(&list);
}

void test_append() {
    printf("Testing append...\n");

    struct dl_list list;
    dl_list_init(&list);

    node_t a, b, c;
    a.val = 1;
    b.val = 2;
    c.val = 3;

    dl_list_append(&list, AS_LIST_NODE(&a));
    dl_list_append(&list, AS_LIST_NODE(&b));
    dl_list_append(&list, AS_LIST_NODE(&c));
    print_list(&list);
}

void test_insertion_sort() {
    printf("Testing insertion sort...\n");

    struct dl_list list;
    dl_list_init(&list);

    node_t a, b, c, d, e, f;
    a.val = 1;
    b.val = 2;
    c.val = 3;
    d.val = 4;
    e.val = 5;
    f.val = 6;

    dl_list_insert(&list, AS_LIST_NODE(&c), cmp);
    dl_list_insert(&list, AS_LIST_NODE(&a), cmp);
    dl_list_insert(&list, AS_LIST_NODE(&b), cmp);
    dl_list_insert(&list, AS_LIST_NODE(&e), cmp);
    dl_list_insert(&list, AS_LIST_NODE(&d), cmp);
    dl_list_insert(&list, AS_LIST_NODE(&f), cmp);
    print_list(&list);
}


int main(int argc, char *argv[]) {
    test_prepend();
    test_append();
    test_insertion_sort();
    return 0;
}