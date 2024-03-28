//
// Created by egbor on 2024-01-30.
//

#ifndef DEV_ARRAY_LIST_H
#define DEV_ARRAY_LIST_H

typedef void *array_list_t;

#include "linked_list.h"
#include <stdbool.h>


/**
 * Creates a new arraylist
 */
extern array_list_t alist_new();


/**
 * Creates a new arraylist with a starting capacity
 * but its reported size would still be zero
 */
extern array_list_t alist_new_init_size(int size);

/**
 * Adds an elem to the back of the list
 *
 * @param array_list: The list to add to
 * @param data: The item to add
 */
extern void alist_push_back(array_list_t array_list, void *data);

/**
 * Gives the nth elem in the list and NULL if index is invalid
 * @param array_list: The retrive from
 * @param idx: The nth elem to retrieve
 */
extern void *alist_nth(array_list_t array_list, int idx);

/**
 * Gives the size of the list
 * @param array_list: The list to find the sizeof
 */
extern int alist_size(array_list_t array_list);

/**
 * WARNING: HIGH RISK OF MEMORY LEAKS
 *
 * Deletes the list but does not deallocates any
 * element in the list
 * @param array_list: The list to deallocate
 */
extern void alist_free_dangle(array_list_t array_list);

/**
 * Deletes the list and deallocates all elem in the list
 * @param array_list: The list to deallocate
 */
extern void alist_free(array_list_t array_list);

/**
 * Removes a value from an index in the list and returns the
 * value if found and NULL if not found
 * @param idx the index to access
 * @return  The value if a valid index is provided and NULL
 *          if the index is out of bounds
 */
extern void *alist_remove_nth(array_list_t array_list, int idx);

/**
 * Removes the first element in the array if it exists,
 * and NULL if it doesnt
 */
extern void *alist_remove_front(array_list_t array_list);

/**
 * Removes the last element in the array if it exists,
 * and NULL if it doesnt
 */
extern void *alist_remove_back(array_list_t array_list);

/**
 * Inserts an element at a specified index in the array list.
 *
 * @param data The item element to insert.
 * @param idx The index at which to insert the element.
 * @return true if the element is successfully inserted, false otherwise.
 */
extern bool alist_insert_nth(array_list_t array_list, void *data, int idx);

/**
 * Maps all the elements in the array based on the function given and
 * returns a new array of mapped item
 *
 * @param map_function The mapping function described by the user
 * @return The new array of mapped item
 */
extern array_list_t alist_map(array_list_t array_list, void *(*map_function)(const void *));

/**
 * Filters all the elements in the array that matches based on the function given and
 * returns a new array of item that passed the filter
 *
 * @param map_function The mapping function described by the user
 * @return The new array of mapped item
 */
extern array_list_t alist_filter(array_list_t array_list, bool (*filter_function)(const void *));

/**
 * Performs an operation on each element in the list
 *
 * @param foreach_function The function to be applied on each element
 */
extern void alist_foreach(array_list_t array_list, void (*foreach_function)(void *));

/**
 * Creates a shallow copy of the array_list passed in
 *
 * @param array_list The list to make a copy of
 * @return The shallow copied list
 */
extern array_list_t alist_copy(array_list_t array_list);

/**
 * Replaces the data at the given index with a given item
 *
 * Cannot be used to insert to the end of the list
 *
 * @param index The index to replace
 * @param item The item to be replaced with
 */
extern void alist_set(array_list_t array_list, int index, void *item);

/**
 * @return Retrieve the first element in the array and null if empty
 */
extern void *alist_peek_front(array_list_t array_list);

/**
 * @return Retrieve the last element in the array and null if empty
 */
extern void *alist_peek_back(array_list_t array_list);

/**
 * Sorts the elements in the list with a comparator
 * @param comparator Passes in the ith and ith + 1 value so that if you want them swapped you return true
 */
extern void alist_sort(array_list_t array_list, bool (*comparator)(void *, void *));

/**
 * Sorts the elements in the list within the bounds of the index provided with a comparator
 * @param comparator Passes in the ith and ith + 1 value so that if you want them swapped you return true
 */
extern void
alist_sort_bounds(array_list_t array_list, bool (*comparator)(void *, void *), int start_index, int end_index);

/**
 * Converts an array list to a linked list
 */
extern linked_list_t alist_to_l_list(array_list_t array_list);

/**
 * For each element and index it passes it into a foreach function you provide
 */
extern void alist_foreach_index(array_list_t array_list, void (*foreach_function)(int, void *));

// An easier for each loop providing the curr elem__ and loop_index__ for each iteration
#define ALIST_FOREACH_ELEM(array_list__, elem__) \
    for (int loop_index__ = 0; \
         loop_index__ < alist_size(array_list__) && \
         (elem__ = alist_nth(array_list__, loop_index__), 1); \
         ++loop_index__)

#endif // DEV_ARRAY_LIST_H

