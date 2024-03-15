//
// Created by egbor on 2024-03-09.
//

#ifndef DEV_LINKED_LIST_H
#define DEV_LINKED_LIST_H

typedef void *linked_list_t;

#include "array_list.h"
#include "../ralphs_stdlib/src_files/linked_list_struct.h"
#include <stdbool.h>

/**
 * Creates a new list
 */
extern linked_list_t l_list_new();

/**
 * Adds an element to the back of a linked list
 * @param data: The item to add
 */
extern void l_list_push_back(linked_list_t linked_list, void *data);

/**
 * Adds an element to the front of a linked list
 */
extern void l_list_add_front(linked_list_t linked_list, void *data);

/**
 * Remove an item from the back of a linked list
 * @return The item removed from the back of the list and returns null if the list is empty
 */
extern void *l_list_remove_back(linked_list_t linked_list);

/**
 * Remove an item from the front of a linked list
 * @return The item removed from the front of the list and returns null if the list is empty
 */
extern void *l_list_remove_front(linked_list_t linked_list);

/**
 * Returns the size of the linked list
 */
extern int l_list_size(linked_list_t linked_list);

/**
 * @return Returns the first elem in the list and NULL if empty
 */
extern void *l_list_peek_front(linked_list_t linked_list);

/**
 * @return Returns the last elem in the list and NULL if empty
 */
extern void *l_list_peek_back(linked_list_t linked_list);

/**
 * Sorts the elements in the list with a comparator
 * @param comparator Passes in the ith and ith + 1 value so that if you want them swapped you return true
 */
extern void l_list_sort(linked_list_t linked_list, bool (*comparator)(void *, void *));

/**
 * Removes an item from the list
 *
 * @param item The item to remove from the list
 * @return Return true if the item is found and false is not
 */
extern bool l_list_remove(linked_list_t linked_list, void *item);

/**
 * Converts a linked list to an array list
 */
extern array_list_t l_list_to_alist(linked_list_t linked_list);

/**
 * Shallow copy the linked list to a new linked list
 */
extern linked_list_t l_list_copy(linked_list_t linked_list);

/**
 * Free linked list and all elements stored in the list
 */
extern void l_list_free(linked_list_t linked_list);

/**
 * Free linked list in the list
 */
extern void l_list_free_dangle(linked_list_t linked_list);

#define L_LIST_FOREACH_LOOP(linked_list__) \
    Llist *llist__ = linked_list__; \
    void *elem__;                          \
    int loop_index__ = 0; \
    for (Ll_node *node__ = llist__->head; \
        node__ != NULL  &&        \
        (elem__ = node__->item);           \
        node__ = node__->next, ++loop_index__) \


#endif //DEV_LINKED_LIST_H
