//
// Created by egbor on 2024-03-09.
//

#include <stdlib.h>
#include <assert.h>
#include "../linked_list.h"
#include "linked_list_struct.h"
#include "../utils.h"

/**
 * Creates a new linked list
 */
linked_list_t new_node(void *data);

linked_list_t new_node(void *data)
{
    Ll_node *node = calloc(1, sizeof(Ll_node));
    node->item = data;
    return node;
}

/**
 * Creates a new linked list
 */
linked_list_t l_list_new()
{
    Llist *l_list = (Llist *) calloc(1, sizeof(Llist));
    assert(l_list != NULL && "Failed to init the linked_list enclosure");

    l_list->size = 0;
    return l_list;
}

/**
 * Returns the size of the linked list
 */
int l_list_size(linked_list_t linked_list)
{
    STDLIB_ASSERT(linked_list, "link_list given is NULL")

    return ((Llist *) linked_list)->size;
}

/**
 * Adds an element to the back of a linked list
 */
void l_list_push_back(linked_list_t linked_list, void *data)
{
    STDLIB_ASSERT(linked_list, "link_list given is NULL")

    Llist *llist = linked_list;
    Ll_node *llNode = new_node(data);
    if (llist->head == NULL)
    {
        llist->head = llNode;
        llist->tail = llist->head;
    } else
    {
        llist->tail->next = llNode;
        llNode->prev = llist->tail;
        llist->tail = llist->tail->next;
    }
    ++llist->size;
}

/**
 * Adds an element to the front of a linked list
 */
void l_list_add_front(linked_list_t linked_list, void *data)
{
    STDLIB_ASSERT(linked_list, "link_list given is NULL")

    Llist *llist = linked_list;
    Ll_node *llNode = new_node(data);
    if (llist->head == NULL)
    {
        llist->head = llNode;
        llist->tail = llist->head;
    } else
    {
        llist->head->prev = llNode;
        llNode->next = llist->head;
        llist->head = llist->head->prev;
    }
    ++llist->size;
}

/**
 * Remove an item from the front of a linked list
 * @return The item removed from the front of the list and returns null if the list is empty
 */
void *l_list_remove_front(linked_list_t linked_list)
{
    STDLIB_ASSERT(linked_list, "link_list given is NULL")

    Llist *llist = linked_list;
    if (llist->size == 0) return NULL;

    void *item = llist->head->item;
    Ll_node *node = llist->head;
    if (llist->size == 1)
    {
        llist->head = NULL;
        llist->tail = NULL;
    } else
    {
        llist->head = llist->head->next;
        llist->head->prev = NULL;
    }

    --llist->size;
    free(node);
    return item;
}


/**
 * Remove an item from the back of a linked list
 * @return The item removed from the back of the list and returns null if the list is empty
 */
void *l_list_remove_back(linked_list_t linked_list)
{
    STDLIB_ASSERT(linked_list, "link_list given is NULL")

    Llist *llist = linked_list;
    if (llist->size == 0) return NULL;

    void *item = llist->tail->item;
    Ll_node *node = llist->tail;
    if (llist->size == 1)
    {
        llist->head = NULL;
        llist->tail = NULL;
    } else
    {
        llist->tail = llist->tail->prev;
        llist->tail->next = NULL;
    }

    --llist->size;
    free(node);
    return item;
}

void l_list_foreach(linked_list_t linked_list, void (*foreach_function)(void *))
{
    STDLIB_ASSERT(linked_list, "link_list given is NULL")

    L_LIST_FOREACH_NODE(linked_list)
    {
        foreach_function(node__->item);
    }
}

/**
 * @return Returns the first elem in the list and NULL if empty
 */
void *l_list_peek_front(linked_list_t linked_list)
{
    STDLIB_ASSERT(linked_list, "link_list given is NULL")

    Llist *llist = linked_list;
    Ll_node *node = llist->head;
    if (node == NULL) return NULL;
    else return node->item;
}

/**
 * @return Returns the last elem in the list and NULL if empty
 */
void *l_list_peek_back(linked_list_t linked_list)
{
    STDLIB_ASSERT(linked_list, "link_list given is NULL")

    Llist *llist = linked_list;
    if (llist->tail == NULL) return NULL;
    else return llist->tail->item;
}

/**
 * Removes an item from the list
 *
 * @param item The item to remove from the list
 * @return Return true if the item is found and false is not
 */
bool l_list_remove(linked_list_t linked_list, void *item)
{
    STDLIB_ASSERT(linked_list, "link_list given is NULL")

    Llist *llist = linked_list;
    if (llist->size == 0) return false;

    if (llist->head->item == item)
    {
        l_list_remove_front(linked_list);
        return true;
    } else if (llist->tail->item == item)
    {
        l_list_remove_back(linked_list);
        return true;
    }

    void *elem;
    L_LIST_FOREACH_ELEM(linked_list, elem)
    {
        if (elem == item)
        {
            Ll_node *prev = node__->prev;
            Ll_node *next = node__->next;
            prev->next = next;
            next->prev = prev;
            free(node__);

            --llist->size;
            return true;
        }
    }

    return false;
}

/**
 * Sorts the elements in the list with a comparator
 * @param comparator Passes in the ith and ith + 1 value so that if you want them swapped you return true
 */
void l_list_sort(linked_list_t linked_list, bool (*comparator)(void *, void *))
{
    STDLIB_ASSERT(linked_list, "link_list given is NULL")

    Llist *llist = linked_list;

    // No sorting needed
    if (llist->size <= 1)
    {
        return;
    }


    Ll_node *current;
    Ll_node *lastSorted = NULL;
    bool swapped;

    do
    {
        swapped = false;
        current = llist->head;

        while (current->next != lastSorted)
        {
            if (comparator(current->item, current->next->item))
            {
                // Swap current and next node's items
                void *temp = current->item;
                current->item = current->next->item;
                current->next->item = temp;
                swapped = true;
            }
            current = current->next;
        }

        lastSorted = current;
    } while (swapped);
}

/**
 * Converts a linked list to an array list
 */
array_list_t l_list_to_alist(linked_list_t linked_list)
{
    STDLIB_ASSERT(linked_list, "link_list given is NULL")

    array_list_t arrayList = alist_new();

    void *elem;
    L_LIST_FOREACH_ELEM(linked_list, elem)
    {
        alist_push_back(arrayList, elem);
    }
    return arrayList;
}

/**
 * Shallow copy the linked list to a new linked list
 */
linked_list_t l_list_copy(linked_list_t linked_list)
{
    linked_list_t copied_list = l_list_new();

    void *elem;
    L_LIST_FOREACH_ELEM(linked_list, elem)
    {
        l_list_push_back(copied_list, elem);
    }

    return copied_list;
}

/**
 * Free linked list and all elements stored in the list
 */
void l_list_free(linked_list_t linked_list)
{
    if (linked_list == NULL) return;

    Llist *llist = linked_list;
    for (Ll_node *node = llist->head; node != NULL;)
    {
        free(node->item);
        Ll_node *prev = node;
        node = node->next;
        free(prev);
    }

    llist->size = 0;
    free(linked_list);
}

void l_list_free_dangle(linked_list_t linked_list)
{
    if (linked_list == NULL) return;

    Llist *llist__ = linked_list;
    for (Ll_node *node__ = llist__->head; node__ != NULL;)
    {
        Ll_node *prev = node__;
        node__ = node__->next;
        free(prev);
    }

    ((Llist *) linked_list)->size = 0;
    free(linked_list);
}
