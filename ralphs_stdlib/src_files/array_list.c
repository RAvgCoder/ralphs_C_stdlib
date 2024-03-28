//
// Created by egbor on 2024-01-30.
//
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../array_list.h"
#include "../utils.h"

#define ALIST_PADDING 10
#define PADDING_SIZE(size, ALIST_PADDING) (((size + ALIST_PADDING) / ALIST_PADDING) * ALIST_PADDING)
#define ALIST_LOAD_CAPACITY 0.7

typedef struct array_list {
    void **data;
    int size;
    int max_capacity;
} Alist;

static void alist_copy_elements(void **src, void **dest, int size);

static void alist_can_grow(Alist *alist);

/**
 * Creates a new arraylist
 */
array_list_t alist_new()
{
    Alist *alist = (Alist *) malloc(sizeof(Alist));
    STDLIB_ASSERT(alist != NULL, "Failed to init the arraylist enclosure Buy more RAM!!")

    alist->size = 0;
    alist->max_capacity = ALIST_PADDING;
    alist->data = calloc(ALIST_PADDING, sizeof(void *));
    STDLIB_ASSERT(alist->data, "Failed to create arraylist Get a new computer bro!!")

    return alist;
}

/**
 * Creates a new arraylist with a starting capacity
 * but its reported size would still be zero
 */
array_list_t alist_new_init_size(int size)
{
    Alist *alist = (Alist *) malloc(sizeof(Alist));
    STDLIB_ASSERT(alist != NULL && size >= 0, "Failed init the arraylist enclosure")

    // Makes the size always aligned with the ALIST_PADDING size
    int padded_size = PADDING_SIZE(size, ALIST_PADDING);

    alist->size = 0;
    alist->max_capacity = padded_size;
    alist->data = calloc(padded_size, sizeof(void *));
    STDLIB_ASSERT(alist->data, "Failed to create arraylist")

    return alist;
}

/**
 * WARNING: HIGH RISK OF MEMORY LEAKS
 *
 * Deletes the list but does not deallocates any
 * element in the list
 * @param array_list: The list to deallocate
 */
void alist_free_dangle(array_list_t array_list)
{
    if (array_list == NULL) return;
    Alist *alist = array_list;
    free(alist->data);
}


/**
 * Deletes the list and deallocates all elem in the list
 * @param array_list: The list to deallocate
 */
void alist_free(array_list_t array_list)
{
    if (array_list == NULL) return;
    Alist *alist = array_list;
    for (int i = 0; i < (int) alist->size; i++)
    {
        free(alist_nth(array_list, i));
    }
    free(alist->data);
}

/**
 * Gives the size of the list
 * @param array_list: The list to find the sizeof
 */
int alist_size(array_list_t array_list)
{
    STDLIB_ASSERT(array_list, "array_list given is NULL")

    return ((Alist *) array_list)->size;
}

/**
 * Adds an elem to the back of the list
 *
 * @param array_list: The list to add to
 * @param data: The item to add
 */
void alist_push_back(array_list_t array_list, void *data)
{
    STDLIB_ASSERT(array_list, "array_list given is NULL")

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
void *alist_nth(array_list_t array_list, int idx)
{
    STDLIB_ASSERT(array_list, "array_list given is NULL")

    Alist *alist = array_list;
    if (!(idx >= 0 && idx < (int) alist->size)) return NULL;
    return alist->data[idx];
}

/**
 *  Removes a value from an index in the list and returns the
 *  value if found and NULL if not found
 */
void *alist_remove_nth(array_list_t array_list, int idx)
{
    STDLIB_ASSERT(array_list, "array_list given is NULL")

    void *value = alist_nth(array_list, idx);
    if (value == NULL) return NULL;

    Alist *alist = array_list;
    for (int i = idx; i < alist->size - 1; i++)
    {
        alist->data[i] = alist->data[i + 1];
    }

    alist->size -= 1;
    return value;
}

/**
 * Removes the first element in the array if it exists,
 * and NULL if it doesnt
 */
void *alist_remove_front(array_list_t array_list)
{
    STDLIB_ASSERT(array_list, "array_list given is NULL")

    return alist_remove_nth(array_list, 0);
}

/**
 * Inserts an element at a specified index in the array list.
 *
 * This function inserts the given item element at the specified index in the array list.
 * If the index is out of bounds, the function returns false.
 * If successful, the element is inserted at the specified index, and the array list is resized if necessary.
 *
 * @param data The item element to insert.
 * @param idx The index at which to insert the element.
 * @return true if the element is successfully inserted, false otherwise.
 */
bool alist_insert_nth(array_list_t array_list, void *data, int idx)
{
    STDLIB_ASSERT(array_list, "array_list given is NULL")

    Alist *alist = array_list;

    // Check if the index is within bounds
    if (!(idx >= 0 && idx <= (alist->size - 1)))
    {
        return false;
    }

    // Ensure capacity for the new element
    alist_can_grow(array_list);

    // Move elements to make space for the new element
    for (int i = alist->size - 1; i >= idx; --i)
    {
        alist->data[i + 1] = alist->data[i];
    }

    // Insert the new element at the specified index
    alist->data[idx] = data;

    return true;
}

/**
 * Inserts an element to the first index of the array
 *
 * @param data The item element to insert.
 * @return true if the element is successfully inserted, false otherwise.
 */
bool alist_insert_front(array_list_t array_list, void *data)
{
    STDLIB_ASSERT(array_list, "array_list given is NULL")

    return alist_insert_nth(array_list, data, 0);
}


/**
 * Removes the last element in the array if it exists,
 * and NULL if it doesnt
 */
void *alist_remove_back(array_list_t array_list)
{
    STDLIB_ASSERT(array_list, "array_list given is NULL")

    return alist_remove_nth(array_list, alist_size(array_list) - 1);
}

/**
 * Maps all the elements in the array based on the function given and
 * returns a new array of mapped item
 *
 * @param map_function The mapping function described by the user
 * @return The new array of mapped item
 */
array_list_t alist_map(array_list_t array_list, void *(*map_function)(const void *))
{
    STDLIB_ASSERT(array_list, "array_list given is NULL")

    Alist *alist = array_list;
    array_list_t mapped_list = alist_new_init_size(alist->size);
    // Add all mapped elements to the new list
    for (int i = 0; i < alist->size; i++)
    {
        alist_push_back(mapped_list, map_function(alist->data[i]));
    }
    return mapped_list;
}


/**
 * Filters all the elements in the array that matches based on the function given and
 * returns a new array of item that passed the filter
 *
 * @param filter_function The filter function described by the user
 * @return The new array of filtered out item
 */
array_list_t alist_filter(array_list_t array_list, bool (*filter_function)(const void *))
{
    STDLIB_ASSERT(array_list, "array_list given is NULL")

    Alist *alist = array_list;
    array_list_t mapped_list = alist_new_init_size(alist->size);
    // Add all mapped elements to the new list
    for (int i = 0; i < alist->size; i++)
    {
        if (filter_function(alist->data[i]))
        {
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
void alist_foreach(array_list_t array_list, void (*foreach_function)(void *))
{
    STDLIB_ASSERT(array_list, "array_list given is NULL")

    Alist *alist = array_list;
    for (int i = 0; i < alist->size; ++i)
    {
        foreach_function(alist->data[i]);
    }
}

/**
 * Creates a shallow copy of the array_list passed in
 *
 * @param array_list The list to make a copy of
 * @return The shallow copied list
 */
array_list_t alist_copy(array_list_t array_list)
{
    STDLIB_ASSERT(array_list, "array_list given is NULL")

    Alist *original_list = array_list;
    Alist *copied_list = alist_new_init_size(original_list->size);
    STDLIB_ASSERT(copied_list, "Failed to create copy list")

    copied_list->size = original_list->size;
    copied_list->max_capacity = original_list->max_capacity;
    alist_copy_elements(original_list->data, copied_list->data, original_list->size);

    return copied_list;
}

void alist_set(array_list_t array_list, int index, void *item)
{
    STDLIB_ASSERT(array_list, "array_list given is NULL")

    Alist *alist = array_list;
    STDLIB_ASSERT(index < alist->size, "Attempting to insert at index %d to array of max index %d", index,
                  alist->size - 1)
    alist->data[index] = item;
}

/**
 * @return Retrieve the first element in the array and null if empty
 */
void *alist_peek_front(array_list_t array_list)
{
    STDLIB_ASSERT(array_list, "array_list given is NULL")

    return alist_nth(array_list, 0);
}

/**
 * @return Retrieve the last element in the array and null if empty
 */
void *alist_peek_back(array_list_t array_list)
{
    STDLIB_ASSERT(array_list, "array_list given is NULL")

    return alist_nth(array_list, alist_size(array_list) - 1);
}

/**
 * Sorts the elements in the list with a comparator
 * @param comparator Passes in the ith and ith + 1 value so that if you want them swapped you return true
 */
void alist_sort(array_list_t array_list, bool (*comparator)(void *, void *))
{
    STDLIB_ASSERT(array_list, "array_list given is NULL")

    int array_size = alist_size(array_list);
    if (array_size <= 1) return;
    alist_sort_bounds(array_list, comparator, 0, array_size - 1);
}

/**
 * Sorts the elements in the list within the bounds of the index provided with a comparator
 * @param comparator Passes in the ith and ith + 1 value so that if you want them swapped you return true
 */
void
alist_sort_bounds(array_list_t array_list, bool (*comparator)(void *, void *), int start_index, int end_index)
{
    STDLIB_ASSERT(array_list, "array_list given is NULL")

    Alist *alist = array_list;

    STDLIB_ASSERT(end_index >= start_index, "End index is less than start index")
    STDLIB_ASSERT(start_index >= 0 && start_index <= alist->size - 1,
                  "Cannot sort as the start index is out of bounds")
    STDLIB_ASSERT(end_index >= 0 && end_index <= alist->size - 1, "Cannot sort as the end index is out of bounds")

    bool swapped = false;
    for (int i = start_index; i < end_index; ++i)
    {
        swapped = false;
        for (int j = start_index; j < end_index; ++j)
        {
            void *item1 = alist->data[j];
            void *item2 = alist->data[j + 1];

            if (comparator(item1, item2))
            {
                alist->data[j] = item2;
                alist->data[j + 1] = item1;
                swapped = true;
            }
        }
        if (!swapped) return;
    }
}

/**
 * Converts an array list to a linked list
 */
linked_list_t alist_to_l_list(array_list_t array_list)
{
    STDLIB_ASSERT(array_list, "array_list given is NULL")

    linked_list_t linkedList = l_list_new();

    void *elem;
    ALIST_FOREACH_ELEM(array_list, elem)
    {
        l_list_push_back(linkedList, elem);
    }
    return linkedList;
}

/**
 * For each element and index it passes it into a foreach function you provide
 */
void alist_foreach_index(array_list_t array_list, void (*foreach_function)(int, void *))
{
    STDLIB_ASSERT(array_list, "array_list given is NULL")

    Alist *alist = array_list;
    for (int i = 0; i < alist->size; ++i)
    {
        foreach_function(i, alist->data[i]);
    }
}

/**
 *  Copy over the elements from src to dest with a max move len of ALIST_PADDING *
 *  @param src: The src list to copy over
 *  @param dest: The dest list to copy over to
 */
static inline void alist_copy_elements(void **src, void **dest, int size)
{
    memcpy(dest, src, size * sizeof(void *));
}

/*
 *  Checks if the list should grow and if so increases the size
 *  of the list
 *
 *  @param alist: The list to grow
 */
static void alist_can_grow(Alist *alist)
{
    // If X% load is reached then grow
    if (alist->size >= (alist->max_capacity * ALIST_LOAD_CAPACITY))
    {
        // Make a new list
        int new_size = PADDING_SIZE(alist->max_capacity, ALIST_PADDING);
        void **new_list = calloc(new_size, sizeof(void *));
        STDLIB_ASSERT(new_list, "Could not grow the list")

        // Move over the elements in the list
        alist_copy_elements(alist->data, new_list, alist->size);

        // Update the list
        alist->max_capacity = new_size;
        free(alist->data);
        alist->data = new_list;
    }
}


