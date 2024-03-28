//
// Created by egbor on 2024-03-09.
//

#ifndef DEV_LINKED_LIST_TEST_H
#define DEV_LINKED_LIST_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include "../linked_list.h"
#include "../utils.h"

void test_l_list_push_back()
{
    printf("Testing l_list_push_back...\n");

    linked_list_t list = l_list_new();
    int data1 = 10;
    int data2 = 20;
    int data3 = 30;

    l_list_push_back(list, &data1);
    l_list_push_back(list, &data2);
    l_list_push_back(list, &data3);

    STDLIB_ASSERT(l_list_size(list) == 3, "Size of the list after push back is not 3")


    // Clean up
    free(list);
}

void test_l_list_add_front()
{
    printf("Testing l_list_add_front...\n");

    linked_list_t list = l_list_new();
    int data1 = 10;
    int data2 = 20;
    int data3 = 30;

    l_list_add_front(list, &data1);
    l_list_add_front(list, &data2);
    l_list_add_front(list, &data3);

    STDLIB_ASSERT(l_list_size(list) == 3, "Size of the list after add front is not 3")


    // Clean up
    free(list);
}

void test_l_list_remove_back()
{
    printf("Testing l_list_remove_back...\n");

    linked_list_t list = l_list_new();
    int data1 = 10;
    int data2 = 20;
    int data3 = 30;

    l_list_push_back(list, &data1);
    l_list_push_back(list, &data2);
    l_list_push_back(list, &data3);

    STDLIB_ASSERT(*(int *) l_list_remove_back(list) == data3, "Removed item from back is incorrect")

    l_list_remove_back(list);
    l_list_remove_back(list);
    l_list_remove_back(list);

    STDLIB_ASSERT(l_list_size(list) == 0, "List is not empty after removing all elements from the back of the list")

    free(list);
}

void test_l_list_remove_front()
{
    printf("Testing l_list_remove_front...\n");

    linked_list_t list = l_list_new();
    int data1 = 10;
    int data2 = 20;
    int data3 = 30;

    l_list_push_back(list, &data1);
    l_list_push_back(list, &data2);
    l_list_push_back(list, &data3);

    STDLIB_ASSERT(*(int *) l_list_remove_front(list) == data1, "Removed item from front is incorrect")

    l_list_remove_front(list);
    l_list_remove_front(list);
    l_list_remove_front(list);

    STDLIB_ASSERT(l_list_size(list) == 0, "List is not empty after remove all elements")

    free(list);
}

void test_l_list_size()
{
    printf("Testing l_list_size...\n");

    linked_list_t list = l_list_new();
    int data1 = 10;

    l_list_push_back(list, &data1);
    l_list_push_back(list, &data1);
    l_list_push_back(list, &data1);

    STDLIB_ASSERT(l_list_size(list) == 3, "Size of the list is incorrect")

    l_list_remove_back(list);
    l_list_remove_back(list);
    l_list_remove_back(list);
    l_list_remove_back(list);

    STDLIB_ASSERT(l_list_size(list) == 0, "Size of the list is incorrect")

    free(list);
}

void test_l_list_peek_front()
{
    printf("Testing l_list_peek_front...\n");

    linked_list_t list = l_list_new();

    char *arr[] = {"I", "am", "a", "boy"};
    l_list_push_back(list, arr[0]);
    l_list_push_back(list, arr[1]);
    l_list_push_back(list, arr[2]);
    l_list_push_back(list, arr[3]);

    char *val = l_list_peek_front(list);
    STDLIB_ASSERT(val == arr[0], "Expected peek front to return %s but it returned %s", arr[0], val)

    l_list_remove_front(list);

    val = l_list_peek_front(list);
    STDLIB_ASSERT(val == arr[1], "Expected peek front to return %s but it returned %s", arr[1], val)
}

void test_l_list_peek_back()
{
    printf("Testing l_list_peek_back...\n");
    linked_list_t list = l_list_new();

    char *arr[] = {"I", "am", "a", "boy"};
    l_list_push_back(list, arr[0]);
    l_list_push_back(list, arr[1]);
    l_list_push_back(list, arr[2]);
    l_list_push_back(list, arr[3]);

    char *val = l_list_peek_back(list);
    STDLIB_ASSERT(val == arr[3], "Expected peek back to return %s but it returned %s", arr[3], val)

    l_list_remove_back(list);

    val = l_list_peek_back(list);
    STDLIB_ASSERT(val == arr[2], "Expected peek back to return %s but it returned %s", arr[2], val)
}

void test_l_list_sort()
{
    printf("Testing l_list_sort...\n");
    linked_list_t list = l_list_new();

    int arr[] = {3, 2, 1, 0};
    l_list_push_back(list, &arr[0]);
    l_list_push_back(list, &arr[1]);
    l_list_push_back(list, &arr[2]);
    l_list_push_back(list, &arr[3]);

    l_list_sort(list, ascending_int_sort);

    int i = -1;

    void *elem;
    L_LIST_FOREACH_ELEM(list, elem)
    {
        int i1 = *(int *) elem;
        STDLIB_ASSERT(i < i1, "List is not in ascending order ith=%d, (ith + 1)=%d", i, i1)
        i = i1;
    }
}

void test_l_list_remove()
{
    printf("Testing l_list_remove...\n");
    linked_list_t list = l_list_new();

    char *arr[] = {"I", "am", "a", "boy"};
    l_list_push_back(list, arr[0]);
    l_list_push_back(list, arr[1]);
    l_list_push_back(list, arr[2]);
    l_list_push_back(list, arr[3]);

    STDLIB_ASSERT(l_list_remove(list, arr[2]), "Failed to remove an element from the list")

    STDLIB_ASSERT(!l_list_remove(list, arr[2]), "Remove should fail but yet succeeded")

    STDLIB_ASSERT(l_list_remove(list, arr[0]), "Failed to remove an element from the list")

    STDLIB_ASSERT(l_list_remove(list, arr[3]), "Failed to remove an element from the list")

    STDLIB_ASSERT(l_list_size(list) == 1, "Size after removal is not correct")
}

void test_l_list_to_alist()
{
    printf("Testing l_list_to_alist...\n");
    linked_list_t linkedList = l_list_new();

    char *arr[] = {"I", "am", "a", "boy"};
    l_list_push_back(linkedList, arr[0]);
    l_list_push_back(linkedList, arr[1]);
    l_list_push_back(linkedList, arr[2]);
    l_list_push_back(linkedList, arr[3]);

    array_list_t arrayList = l_list_to_alist(linkedList);

    STDLIB_ASSERT(l_list_size(linkedList) == alist_size(arrayList), "Size of copied list doesnt match the original")

    void *elem;
    int loop_index;
    L_LIST_FOREACH_INDEX(linkedList, elem, loop_index)
    {
        char *val = alist_nth(arrayList, loop_index);
        STDLIB_ASSERT(elem == val,
                      "Conversion of a linked list to array_list failed at index:%d Expected:%s, Received:%s",
                      loop_index, val, (char *) elem)
    }
}

void test_l_list_copy()
{
    printf("Testing l_list_copy...\n");
    linked_list_t linkedList = l_list_new();

    char *arr[] = {"I", "am", "a", "boy"};
    l_list_push_back(linkedList, arr[0]);
    l_list_push_back(linkedList, arr[1]);
    l_list_push_back(linkedList, arr[2]);
    l_list_push_back(linkedList, arr[3]);

    linked_list_t linkedListCopy = l_list_copy(linkedList);

    STDLIB_ASSERT(l_list_size(linkedList) == l_list_size(linkedList), "Size of copied list doesnt match the original")

    STDLIB_ASSERT(l_list_remove(linkedListCopy, arr[0]), "Copy failed")
    STDLIB_ASSERT(l_list_remove(linkedListCopy, arr[1]), "Copy failed")
    STDLIB_ASSERT(l_list_remove(linkedListCopy, arr[2]), "Copy failed")
    STDLIB_ASSERT(l_list_remove(linkedListCopy, arr[3]), "Copy failed")

    STDLIB_ASSERT(l_list_size(linkedListCopy) == 0, "Removed all elem in the list but size isn't zero")
}

/* Function to run all tests */
void l_list_test_all()
{
    /* Run tests */
    printf("// ------- [ LINKED LIST TEST ] ------- \\\\ \n");

    test_l_list_push_back();
    test_l_list_add_front();
    test_l_list_remove_back();
    test_l_list_remove_front();
    test_l_list_size();
    test_l_list_peek_front();
    test_l_list_peek_back();
    test_l_list_sort();
    test_l_list_remove();
    test_l_list_to_alist();
    test_l_list_copy();

    printf("All tests passed successfully.\n\n");
}

#endif //DEV_LINKED_LIST_TEST_H
