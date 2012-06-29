#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "monad.h"

struct list;
typedef struct list list_t;

struct list
{
    void*   val;
    list_t* next;
};

list_t* new_node(void* v)
{
    list_t* l = malloc(sizeof(list_t));
    l->val    = v;
    l->next   = NULL;
}

list_t* cons(void* v, list_t* l)
{
    list_t* node = new_node(v);
    node->next = l;
    return node;
}

list_t* last(list_t* l)
{
    if(!l) return NULL;

    list_t* a = l;
    list_t* b = l->next;
    while(b) {
        a = b;
        b = b->next;
    }
    return a;
}

void append(void* v, list_t* l)
{
    list_t* last_elem = last(l);
    list_t* node = node_new(v);
    l->next = node;
}

void concat(list_t* head, list_t* tail)
{
    list_t* head_end = last(head);
    head_end->next = tail;
}

list_t* map(list_t* l, void* (*f)(void*))
{
}
