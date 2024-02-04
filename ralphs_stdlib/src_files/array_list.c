//
// Created by egbor on 2024-01-30.
//
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "../array_list.h"

#define ALIST_PADDING 10
#define ALIST_LOAD_CAPACITY 0.7

typedef struct array_list {
    void **data;
    int size;
    int max_capacity;
} Alist;

// Functions
static void alist_move_elements(void **src, void **dest, int size);

static void alist_can_grow(Alist *alist);

/**
 * Creates a new arraylist
 */
array_list_t alist_new() {
    Alist *alist = (Alist *) malloc(sizeof(Alist));
    assert(alist != NULL && "Failed init the arraylist enclosure");

    alist->size = 0;
    alist->max_capacity = ALIST_PADDING;
    alist->data = calloc(ALIST_PADDING, sizeof(void *));
    assert(alist->data && "Failed to create arraylist");

    return alist;
}

/**
 * Creates a new arraylist with a starting capacity
 * but its reported size would still be zero
 */
array_list_t alist_new_init_size(int size) {
    Alist *alist = (Alist *) malloc(sizeof(Alist));
    assert(alist != NULL && size >= 0 && "Failed init the arraylist enclosure");

    // Makes the size always aligned with the ALIST_PADDING size
    int padded_size = ((size + ALIST_PADDING) / ALIST_PADDING) * ALIST_PADDING;

    alist->size = 0;
    alist->max_capacity = padded_size;
    alist->data = calloc(padded_size, sizeof(void *));
    assert(alist->data && "Failed to create arraylist");

    return alist;
}

/**
 * WARNING: HIGH RISK OF MEMORY LEAKS
 *
 * Deletes the list but does not deallocates any
 * element in the list
 * @param array_list: The list to deallocate
 */
void alist_free_dangle(array_list_t array_list) {
    Alist *alist = array_list;
    free(alist->data);
}


/**
 * Deletes the list and deallocates all elem in the list
 * @param array_list: The list to deallocate
 */
void alist_free(array_list_t array_list) {
    if (array_list == NULL) return;
    Alist *alist = array_list;
    for (int i = 0; i < (int) alist->size; i++) {
        free(alist_nth(array_list, i));
    }
    free(alist->data);
    array_list = NULL;
}

/**
 * Gives the size of the list
 * @param array_list: The list to find the sizeof
 */
size_t alist_size(array_list_t array_list) {
    return ((Alist *) array_list)->size;
}

/**
 * Adds an elem to the back of the list
 *
 * @param array_list: The list to add to
 * @param data: The data to add
 */
void alist_push_back(array_list_t array_list, void *data) {
    Alist *alist = array_list;
    alist_can_grow(alist);
    alist->data[alist->size] = data;
    alist->size += 1;
}

/**
 * Gives the nth elem in the list
 * @param array_list: The retrive from
 * @param idx: The nth elem to retrieve
 */
void *alist_nth(array_list_t array_list, int idx) {
    Alist *alist = array_list;
    if (!(idx >= 0 && idx < (int) alist->size)) return NULL;
    return alist->data[idx];
}

/**
 *  Removes a value from an index in the list and returns the
 *  value if found and NULL if not found
 */
void *alist_remove_nth(array_list_t array_list, int idx) {
    void *value = alist_nth(array_list, idx);
    if (value == NULL) return NULL;

    Alist *alist = array_list;
    for (int i = 0; i < alist->size - 1; i++) {
        alist->data[i] = alist->data[i + 1];
    }

    alist->size -= 1;
    return value;
}

/**
 * Removes the first element in the array if it exists,
 * and NULL if it doesnt
 */
void *alist_remove_front(array_list_t array_list) {
    return alist_remove_nth(array_list, 0);
}

/**
 * Inserts an element at a specified index in the array list.
 *
 * This function inserts the given data element at the specified index in the array list.
 * If the index is out of bounds, the function returns false.
 * If successful, the element is inserted at the specified index, and the array list is resized if necessary.
 *
 * @param data The data element to insert.
 * @param idx The index at which to insert the element.
 * @return true if the element is successfully inserted, false otherwise.
 */
bool alist_insert_nth(array_list_t array_list, void *data, int idx) {
    Alist *alist = array_list;

    // Check if the index is within bounds
    if (!(idx >= 0 && idx <= (alist->size - 1))) {
        return false;
    }

    // Ensure capacity for the new element
    alist_can_grow(array_list);

    // Move elements to make space for the new element
    for (int i = alist->size - 1; i >= idx; --i) {
        alist->data[i + 1] = alist->data[i];
    }

    // Insert the new element at the specified index
    alist->data[idx] = data;

    return true;
}

/**
 * Inserts an element to the first index of the array
 *
 * @param data The data element to insert.
 * @return true if the element is successfully inserted, false otherwise.
 */
bool alist_insert_front(array_list_t array_list, void *data) {
    return alist_insert_nth(array_list, data, 0);
}


/**
 * Removes the last element in the array if it exists,
 * and NULL if it doesnt
 */
void *alist_remove_back(array_list_t array_list) {
    return alist_remove_nth(array_list, alist_size(array_list) - 1);
}

/**
 * Maps all the elements in the array based on the function given and
 * returns a new array of mapped data
 *
 * @param map_function The mapping function described by the user
 * @return The new array of mapped data
 */
array_list_t alist_map(array_list_t array_list, void *(*map_function)(const void *)) {
    Alist *alist = array_list;
    array_list_t mapped_list = alist_new_init_size(alist->size);
    // Add all mapped elements to the new list
    for (int i = 0; i < alist->size; i++) {
        alist_push_back(mapped_list, map_function(alist->data[i]));
    }
    return mapped_list;
}


/**
 * Filters all the elements in the array that matches based on the function given and
 * returns a new array of data that passed the filter
 *
 * @param filter_function The filter function described by the user
 * @return The new array of filtered out data
 */
array_list_t alist_filter(array_list_t array_list, bool (*filter_function)(const void *)) {
    Alist *alist = array_list;
    array_list_t mapped_list = alist_new_init_size(alist->size);
    // Add all mapped elements to the new list
    for (int i = 0; i < alist->size; i++) {
        if (filter_function(alist->data[i])) {
            alist_push_back(mapped_list, alist->data[i]);
        }
    }
    return mapped_list;
}

/**
 * Performs an operation on each element in the list
 *
 * @param foreach_function The function to be applied on each element
 */
void alist_foreach(array_list_t array_list, void (*foreach_function)(void *)) {
    Alist *alist = array_list;
    for (int i = 0; i < alist->size; ++i) {
        foreach_function(alist->data[i]);
    }
}


/**
 *  Moves over the elements from src to dest with a max move len of ALIST_PADDING *
 *  @param src: The src list to copy over
 *  @param dest: The dest list to copy over to
 */
static void alist_move_elements(void **src, void **dest, int size) {
    memcpy(dest, src, size * sizeof(void *));
}

/*
 *  Checks if the list should grow and if so increases the size
 *  of the list
 *
 *  @param alist: The list to grow
 */
static void alist_can_grow(Alist *alist) {
    // If X% load is reached then grow
    if (alist->size >= (alist->max_capacity * ALIST_LOAD_CAPACITY)) {
        // Make a new list
        void **new_list = calloc(alist->max_capacity + ALIST_PADDING, sizeof(void *));
        assert(new_list && "Could not grow the list");

        // Move over the elements in the list
        alist_move_elements(alist->data, new_list, alist->size);

        // Update the list
        alist->max_capacity += ALIST_PADDING;
        free(alist->data);
        alist->data = new_list;
    }
}


