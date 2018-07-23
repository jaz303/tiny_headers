#ifndef JLIB_LIST_IMPL

#ifndef JLIB_LIST_H
#define JLIB_LIST_H

struct list_node;
struct list_node {
    struct list_node *prev, *next;
};

#define AS_LIST_NODE(v) ((struct list_node*)v)

struct dl_list {
    struct list_node *head, *tail;
    int count;
};

struct circular_list {
    struct list_node *head;
    int count;
};

typedef int (list_compare_fn)(void *l, void *r);
typedef void (list_walk_fn)(void *v, int ix);

void dl_list_init(struct dl_list *l);
void dl_list_append(struct dl_list *l, struct list_node *n);
void dl_list_prepend(struct dl_list *l, struct list_node *n);
void dl_list_insert_before(struct dl_list *l, struct list_node *n, struct list_node *rel);
void dl_list_insert_after(struct dl_list *l, struct list_node *n, struct list_node *rel);
void dl_list_insert(struct dl_list *l, struct list_node *n, list_compare_fn *cmp);
void dl_list_remove(struct dl_list *l, struct list_node *n);
void dl_list_walk(struct dl_list *l, list_walk_fn *cb);

void circular_list_init(struct circular_list *l);
void circular_list_insert_before_head(struct circular_list *l, struct list_node *n);
void circular_list_insert_after_head(struct circular_list *l, struct list_node *n);
void circular_list_remove(struct circular_list *l, struct list_node *n);
void circular_list_advance(struct circular_list *l);

#endif

#else

/* Doubly Linked List */

void dl_list_init(struct dl_list *l) {
    l->head = l->tail = 0;
    l->count = 0;
}

void dl_list_append(struct dl_list *l, struct list_node *n) {
    if (l->count == 0) {
        n->prev = n->next = 0;
        l->head = l->tail = n;
        l->count = 1;
    } else {
        n->prev = l->tail;
        n->next = 0;
        l->tail->next = n;
        l->tail = n;
        l->count++;
    }
}

void dl_list_prepend(struct dl_list *l, struct list_node *n) {
    if (l->count == 0) {
        n->prev = n->next = 0;
        l->head = l->tail = n;
        l->count = 1;   
    } else {
        n->prev = 0;
        n->next = l->head;
        l->head->prev = n;
        l->head = n;
        l->count++;
    }
}

void dl_list_insert_before(struct dl_list *l, struct list_node *n, struct list_node *rel) {
    n->next = rel;
    n->prev = rel->prev;
    if (rel == l->head) {
        l->head = n;
    } else {
        rel->prev->next = n;
    }
    rel->prev = n;
    l->count++;
}

void dl_list_insert_after(struct dl_list *l, struct list_node *n, struct list_node *rel) {
    n->next = rel->next;
    n->prev = rel;
    if (rel == l->tail) {
        l->tail = n;
    } else {
        rel->next->prev = n;
    }
    rel->next = n;
    l->count++; 
}

void dl_list_insert(struct dl_list *l, struct list_node *n, list_compare_fn *cmp) {
    if (l->count == 0) {
        dl_list_append(l, n);
    } else {
        struct list_node *tmp = l->head;
        while (tmp) {
            if (cmp(n, tmp) < 0) {
                dl_list_insert_before(l, n, tmp);
                return;
            }
            tmp = tmp->next;
        }
        dl_list_insert_after(l, n, l->tail);
    }
}

void dl_list_remove(struct dl_list *l, struct list_node *n) {
    // if (n == l->head) {
        
    // }
    // if (n->prev) {
    //  n->prev->next = n->next;
    // }
    
    // if (n->next) {
    //  n->next->prev = n->prev;
    // }

    // l->count--;
}

void dl_list_walk(struct dl_list *l, list_walk_fn *cb) {
    struct list_node *tmp = l->head;
    int ix = 0;
    while (tmp) {
        cb(tmp, ix);
        tmp = tmp->next;
        ix++;
    }
}

/* Circular List */

void circular_list_init(struct circular_list *l) {
    l->head = 0;
    l->count = 0;
}

void circular_list_insert_before_head(struct circular_list *l, struct list_node *n) {
    if (l->count == 0) {
        l->head = n->prev = n->next = n;
        l->count = 1;
    } else {
        n->next = l->head;
        n->prev = l->head->prev;
        l->head->prev->next = n;
        l->head->prev = n;
        l->count++;
    }
}

void circular_list_insert_after_head(struct circular_list *l, struct list_node *n) {
    if (l->count == 0) {
        l->head = n->prev = n->next = n;
        l->count = 1;
    } else {
        n->prev = l->head;
        n->next = l->head->next;
        l->head->next->prev = n;
        l->head->next = n;
        l->count++;
    }   
}

void circular_list_remove(struct circular_list *l, struct list_node *n) {
    if (l->count == 1) {
        l->head = 0;
        l->count = 0;
    } else {
        if (n == l->head) {
            l->head = n->next;
        }
        n->prev->next = n->next;
        n->next->prev = n->prev;
        l->count--;
    }
}

void circular_list_advance(struct circular_list *l) {
    if (l->count > 0) {
        l->head = l->head->next;
    }
}

#endif