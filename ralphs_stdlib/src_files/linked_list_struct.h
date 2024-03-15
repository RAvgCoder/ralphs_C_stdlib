//
// Created by egbor on 2024-03-09.
//

#ifndef DEV_LINKED_LIST_STRUCT_H
#define DEV_LINKED_LIST_STRUCT_H



typedef struct node {
    void *item;
    struct node *next;
    struct node *prev;
} Ll_node;

typedef struct linked_list {
    Ll_node *head;
    Ll_node *tail;
    int size;
} Llist;

#endif //DEV_LINKED_LIST_STRUCT_H
