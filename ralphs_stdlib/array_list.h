//
// Created by egbor on 2024-01-30.
//
#pragma once

#include <stdbool.h>

typedef void *array_list_t;

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
 * @param data: The data to add
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
extern size_t alist_size(array_list_t array_list);

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
 * @param data The data element to insert.
 * @param idx The index at which to insert the element.
 * @return true if the element is successfully inserted, false otherwise.
 */
extern bool alist_insert_nth(array_list_t array_list, void *data, int idx);

/**
 * Maps all the elements in the array based on the function given and
 * returns a new array of mapped data
 *
 * @param map_function The mapping function described by the user
 * @return The new array of mapped data
 */
extern array_list_t alist_map(array_list_t array_list, void *(*map_function)(const void *));

/**
 * Filters all the elements in the array that matches based on the function given and
 * returns a new array of data that passed the filter
 *
 * @param map_function The mapping function described by the user
 * @return The new array of mapped data
 */
extern array_list_t alist_filter(array_list_t array_list, bool (*filter_function)(const void *));

/**
 * Performs an operation on each element in the list
 *
 * @param foreach_function The function to be applied on each element
 */
extern void alist_foreach(array_list_t array_list, void (*foreach_function)(void *));


