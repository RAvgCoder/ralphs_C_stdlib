//
// Created by egbor on 2024-01-31.
//

#ifndef AS2_ARRAYLIST_TEST_H
#define AS2_ARRAYLIST_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../array_list.h"
#include "../utils.h"

/* Test function prototypes */
void test_alist_map();

void *map_x10_helper(const void *int_data);

void test_alist_filter();

bool filter_mod2_helper(const void *int_data);

void test_alist_foreach();

void foreach_x10_helper(void *int_data);

bool ascending_int_sort(void *a, void *b);

void foreach_times_index_helper(int idx, void *item);


/* Test cases */
void test_alist_new()
{
    printf("Testing alist_new...\n");
    array_list_t list = alist_new();
    STDLIB_ASSERT(list != NULL, "List created was null and expected non-NULL")
    alist_free_dangle(list);
}

void test_alist_new_init_size()
{
    printf("Testing alist_new_init_size...\n");
    int init_size = 21;
    array_list_t list = alist_new_init_size(init_size);
    array_list_t list1 = alist_new();

    // Checks the pointer offset where it expects max_capacity(PADDING USED) to be
    int PADDING = *((int *) (list1 + sizeof(void *) + sizeof(int)));
    init_size = ((init_size + PADDING) / PADDING) * PADDING; // 30

    int size = *((int *) (list + sizeof(void *) + sizeof(int)));

    STDLIB_ASSERT(size == init_size, "Size of max capacity is not set Expected: %d, Gotten: %d", init_size, size)

    alist_free_dangle(list);
    alist_free_dangle(list1);

}

void test_alist_push_back()
{
    printf("Testing alist_push_back...\n");
    array_list_t list = alist_new();

    size_t data1 = 10;
    alist_push_back(list, &data1);
    STDLIB_ASSERT(alist_size(list) == 1, "Expected num of elements in the array to be 1 but found %d", alist_size(list))

    size_t gotten = *(size_t *) alist_nth(list, 0);
    STDLIB_ASSERT(gotten == data1, "Value gotten from the array was %zu but got %zu", data1, gotten)

    alist_free_dangle(list);
}

void test_alist_nth()
{
    printf("Testing alist_nth...\n");
    array_list_t list = alist_new();

    int data1 = 10;
    alist_push_back(list, &data1);

    STDLIB_ASSERT(alist_nth(list, 0) != NULL, "Data gotten at index 0 is expected to be non-null")
    STDLIB_ASSERT(alist_nth(list, -1) == NULL, "Data gotten at index 0 is expected to be null")

    int gotten = *(int *) alist_nth(list, 0);
    STDLIB_ASSERT(gotten == data1, "Data gotten seems to not match expected Gotten: %d, Expected %d", gotten, data1)

    alist_free_dangle(list);
}

void test_alist_size()
{
    printf("Testing alist_size...\n");
    array_list_t list = alist_new();

    int data1 = 10;
    alist_push_back(list, &data1);
    STDLIB_ASSERT(alist_size(list) == 1, "Pushed only one element but but size reported says %d", alist_size(list))

    alist_free_dangle(list);
}

void test_alist_free_dangle()
{
    printf("Testing alist_free_dangle...\n");
    array_list_t list = alist_new();
    alist_free_dangle(list); // Just to ensure no crashes
}

void test_alist_free()
{
    printf("Testing alist_free...\n");
    array_list_t list = alist_new();

    int *ptr = (int *) calloc(10, sizeof(int));
    alist_push_back(list, ptr);
    alist_free(list); // Ensure no memory leaks
    alist_free(NULL); // Ensure no free of NULL values
}

void test_alist_remove_nth()
{
    printf("Testing alist_remove_nth...\n");
    array_list_t list = alist_new();

    char *arr[] = {"I", "am", "a", "boy"};
    alist_push_back(list, arr[0]);
    alist_push_back(list, arr[1]);
    alist_push_back(list, arr[2]);
    alist_push_back(list, arr[3]);

    char *val = alist_remove_nth(list, 0);
    STDLIB_ASSERT(val == arr[0], "Removing a valid element failed. Returned %s Expected %s", val, arr[0])

    val = alist_remove_nth(list, 3);
    STDLIB_ASSERT(val == NULL, "Removing an invalid index should return NULL but returned %s", val)

    val = alist_remove_nth(list, 0);
    STDLIB_ASSERT(val == arr[1], "Removing an invalid index should return %s but returned %s", arr[1], val)

    val = alist_remove_nth(list, 0);
    STDLIB_ASSERT(val == arr[2], "Removing an invalid index should return %s but returned %s", arr[2], val)

    val = alist_remove_nth(list, 0);
    STDLIB_ASSERT(val == arr[3], "Removing an invalid index should return %s but returned %s", arr[3], val)

    STDLIB_ASSERT(alist_size(list) == 0, "Size after removal is expected to be zero but was %d", alist_size(list))

    alist_free_dangle(list);
}

void test_alist_remove_front()
{
    printf("Testing alist_remove_front...\n");
    array_list_t list = alist_new();

    int first = 0;
    int second = 1;
    alist_push_back(list, &first);
    alist_push_back(list, &second);

    alist_remove_front(list);

    int gotten = *((int *) alist_nth(list, 0));
    STDLIB_ASSERT(gotten == second, "Removing from the front of the list failed Expected %d, Got %d", second, gotten)

    alist_free_dangle(list);

}

void test_alist_remove_back()
{
    printf("Testing alist_remove_back...\n");
    array_list_t list = alist_new();

    int first = 0;
    int second = 1;
    alist_push_back(list, &first);
    alist_push_back(list, &second);

    alist_remove_back(list);

    int *gotten = alist_nth(list, 1);
    STDLIB_ASSERT(gotten == NULL, "Removing from the front of the list failed Expected NULL, Got %d", *gotten)

    alist_free_dangle(list);
}

void test_alist_insert_nth()
{
    printf("Testing alist_insert_nth...\n");
    array_list_t list = alist_new();

    int first = 1;
    int second = 2;
    int third = 3;
    alist_push_back(list, &first);
    alist_push_back(list, &third);

    alist_insert_nth(list, &second, 1);

    int gotten = *((int *) alist_nth(list, 1));
    STDLIB_ASSERT(gotten == second,
                  "Inserting into the list failed Expected %d to be at the position of insertion, but got %d", second,
                  gotten)

    alist_free_dangle(list);
}

void test_alist_map()
{
    printf("Testing alist_map...\n");
    array_list_t list = alist_new();
    int MAX_ITER = 10;

    for (int i = 0; i < MAX_ITER; i++)
    {
        int *x = malloc(sizeof(int));
        assert(x && "Could not create item for mapping");
        *x = i;
        alist_push_back(list, x);
    }

    array_list_t mapped_list = alist_map(list, map_x10_helper);

    for (int i = 0; i < MAX_ITER; ++i)
    {
        int n = *(int *) alist_nth(mapped_list, i);
        STDLIB_ASSERT(n == (i * 10), "Mapping failed Expected  %d, but Got: %d", (i * 10), n)
    }

    alist_free(list);
    alist_free(mapped_list);
}

void *map_x10_helper(const void *int_data)
{
    int *mapped = malloc(sizeof(int));
    assert(mapped && "Could not create item for re-mapping");
    *mapped = *((int *) int_data) * 10;
    return mapped;
}

void test_alist_filter()
{
    printf("Testing alist_filter...\n");
    array_list_t list = alist_new();
    int MAX_ITER = 10;

    for (int i = 0; i < MAX_ITER; i++)
    {
        int *x = malloc(sizeof(int));
        assert(x && "Could not create item for mapping");
        *x = i;
        alist_push_back(list, x);
    }

    array_list_t filtered_list = alist_filter(list, filter_mod2_helper);

    STDLIB_ASSERT(alist_size(filtered_list) == (MAX_ITER / 2),
                  "Filtered item size doesnt match Expected: %d, Got: %d", (MAX_ITER / 2), alist_size(filtered_list))

    int i = 0;
    for (int mod_check = 0; mod_check < MAX_ITER; mod_check += 2)
    {
        int n = *(int *) alist_nth(filtered_list, i);

        STDLIB_ASSERT(n == mod_check, "Mapping failed Expected  %d, but Got: %d", mod_check, n)

        i++;
    }

    alist_free(list);
    alist_free_dangle(filtered_list);
}

bool filter_mod2_helper(const void *int_data)
{
    return (*((int *) int_data) % 2) == 0;
}

void test_alist_foreach()
{
    printf("Testing alist_foreach...\n");
    array_list_t list = alist_new();
    const int MAX_ITER = 10;

    for (int i = 0; i < MAX_ITER; i++)
    {
        int *x = malloc(sizeof(int));
        assert(x && "Could not create item for mapping");
        *x = i;
        alist_push_back(list, x);
    }

    alist_foreach(list, foreach_x10_helper);

    for (int i = 0; i < MAX_ITER; ++i)
    {
        int n = *(int *) alist_nth(list, i);
        int x = i;
        foreach_x10_helper(&x);
        STDLIB_ASSERT(n == x, "Foreach function Expects output %d, but got %d", x, n);
    }

    alist_free(list);
}

void foreach_x10_helper(void *int_data)
{
    *((int *) int_data) *= 10;
}

void test_alist_copy()
{
    printf("Testing alist_copy...\n");
    array_list_t original = alist_new();

    char *arr[] = {"I", "am", "a", "boy"};
    alist_push_back(original, arr[0]);
    alist_push_back(original, arr[1]);
    alist_push_back(original, arr[2]);
    alist_push_back(original, arr[3]);

    array_list_t copied_list = alist_copy(original);

    STDLIB_ASSERT(alist_size(copied_list) == alist_size(original),
                  "Copied original size does not match the original original.\nCopied size is %d",
                  alist_size(copied_list))

    ALIST_FOREACH_LOOP(copied_list)
    {
        char *val = (char *) alist_nth(original, loop_index__);
        STDLIB_ASSERT(elem__ == val, "Words dont match for index %d, Copied: %s, Original: %s", loop_index__,
                      (char *) elem__, val);
    }

    alist_free_dangle(original);
    alist_free_dangle(copied_list);
}


void test_alist_set()
{
    printf("Testing alist_set...\n");
    array_list_t list = alist_new();

    char *arr[] = {"I", "am", "a", "boy"};
    alist_push_back(list, arr[0]);
    alist_push_back(list, arr[1]);
    alist_push_back(list, arr[2]);
    alist_push_back(list, arr[3]);

    alist_set(list, 0, arr[3]);
    alist_set(list, 1, arr[2]);
    alist_set(list, 2, arr[1]);
    alist_set(list, 3, arr[0]);

    ALIST_FOREACH_LOOP(list)
    {
        char *val = arr[3 - loop_index__];
        STDLIB_ASSERT(elem__ == val, "Element was not set at index %d for Set:%s, Original:%s", loop_index__,
                      (char *) elem__, val)
    }
}

void test_alist_peek_front()
{
    printf("Testing alist_peek_front...\n");
    array_list_t list = alist_new();

    STDLIB_ASSERT(alist_peek_front(list) == NULL, "Retrieving the first element from an empty list didn't return NULL")

    char *arr[] = {"I", "am", "a", "boy"};
    alist_push_back(list, arr[0]);
    alist_push_back(list, arr[1]);
    alist_push_back(list, arr[2]);
    alist_push_back(list, arr[3]);

    char *val = alist_peek_front(list);
    STDLIB_ASSERT(val == arr[0], "Retrieving the first element from was '%s' but it's ment to be '%s'", val, arr[0])

    alist_remove_front(list);

    val = alist_peek_front(list);
    STDLIB_ASSERT(val == arr[1],
                  "Retrieving the first element after removal from an empty list was '%s' but it's ment to be '%s'",
                  val, arr[1])
}

void test_alist_peek_back()
{
    printf("Testing alist_peek_back...\n");
    array_list_t list = alist_new();

    STDLIB_ASSERT(alist_peek_back(list) == NULL, "Retrieving the last element from an empty list didn't return NULL")

    char *arr[] = {"I", "am", "a", "boy"};
    alist_push_back(list, arr[0]);
    alist_push_back(list, arr[1]);
    alist_push_back(list, arr[2]);
    alist_push_back(list, arr[3]);

    char *val = alist_peek_back(list);
    STDLIB_ASSERT(val == arr[3], "Retrieving the last element from was '%s' but it's ment to be '%s'", val, arr[3])

    alist_remove_back(list);

    val = alist_peek_back(list);
    STDLIB_ASSERT(val == arr[2],
                  "Retrieving the last element after the removal of the last element was '%s' but it's ment to be '%s'",
                  val, arr[2])
}

bool ascending_int_sort(void *a, void *b)
{
    int a1 = *((int *) a);
    int b1 = *((int *) b);
    return a1 > b1;
}

void test_alist_sort()
{
    printf("Testing alist_sort...\n");
    array_list_t list = alist_new();

    int arr[] = {3, 2, 1, 0};
    alist_push_back(list, &arr[0]);
    alist_push_back(list, &arr[1]);
    alist_push_back(list, &arr[2]);
    alist_push_back(list, &arr[3]);

    alist_sort(list, ascending_int_sort);

    ALIST_FOREACH_LOOP(list)
    {
        if (loop_index__ == 3) break;
        int i = *(int *) elem__;
        int i1 = *(int *) alist_nth(list, loop_index__ + 1);
        STDLIB_ASSERT(i < i1, "List is not in ascending order ith=%d, (ith + 1)=%d", i, i1)
    }
}

void test_alist_sort_bound()
{
    printf("Testing alist_sort_bound...\n");
    array_list_t list = alist_new();

    int arr[] = {3, 2, 1, 0};
    alist_push_back(list, &arr[0]);
    alist_push_back(list, &arr[1]);
    alist_push_back(list, &arr[2]);
    alist_push_back(list, &arr[3]);

    alist_sort_bounds(list, ascending_int_sort, 1, 2);

    int val = *(int *) alist_nth(list, 0);
    STDLIB_ASSERT(val == arr[0], "Bounds sorting failed, Expected %d, Found %d", arr[0], val)

    val = *(int *) alist_nth(list, 3);
    STDLIB_ASSERT(val == arr[3], "Bounds sorting failed, Expected %d, Found %d", arr[3], val)

    val = *(int *) alist_nth(list, 2);
    STDLIB_ASSERT(val == arr[1], "Bounds sorting failed, Expected %d, Found %d", arr[1], val)

    val = *(int *) alist_nth(list, 1);
    STDLIB_ASSERT(val == arr[2], "Bounds sorting failed, Expected %d, Found %d", arr[2], val)
}

void test_alist_to_l_list()
{
    printf("Testing alist_to_l_list...\n");
    array_list_t arrayList = alist_new();

    char *arr[] = {"I", "am", "a", "boy"};
    alist_push_back(arrayList, arr[0]);
    alist_push_back(arrayList, arr[1]);
    alist_push_back(arrayList, arr[2]);
    alist_push_back(arrayList, arr[3]);

    linked_list_t linkedList = alist_to_l_list(arrayList);

    L_LIST_FOREACH_LOOP(linkedList)
    {
        char *val = alist_nth(arrayList, loop_index__);
        STDLIB_ASSERT(val == elem__, "Copied list doesnt match at index: %d, Expected:%s Found:%s", loop_index__, val,
                      (char *) elem__);
    }
}

void foreach_times_index_helper(int idx, void *item)
{
    *((int *) item) *= idx;
}

void test_alist_foreach_index()
{
    printf("Testing alist_foreach_index...\n");
    array_list_t arrayList = alist_new();

    int arr[] = {3, 2, 1, 0};
    alist_push_back(arrayList, &arr[0]);
    alist_push_back(arrayList, &arr[1]);
    alist_push_back(arrayList, &arr[2]);
    alist_push_back(arrayList, &arr[3]);

    alist_foreach_index(arrayList, foreach_times_index_helper);

    ALIST_FOREACH_LOOP(arrayList)
    {
        int expected = *((int *) elem__) *= loop_index__;
        int actual = *((int *) elem__);
        STDLIB_ASSERT(actual == expected, "For each index function failed at index:%d Expected:%d, Received:%d",
                      loop_index__, expected, actual)
    }
}

int alist_test_all()
{
    printf("// ------- [ ARRAY LIST TEST ] ------- \\\\ \n");

    /* Run tests */
    test_alist_new();
    test_alist_new_init_size();
    test_alist_push_back();
    test_alist_nth();
    test_alist_size();
    test_alist_free_dangle();
    test_alist_free();
    test_alist_remove_nth();
    test_alist_remove_front();
    test_alist_remove_back();
    test_alist_insert_nth();
    test_alist_map();
    test_alist_filter();
    test_alist_foreach();
    test_alist_copy();
    test_alist_set();
    test_alist_peek_front();
    test_alist_peek_back();
    test_alist_sort();
    test_alist_sort_bound();
    test_alist_to_l_list();
    test_alist_foreach_index();

    printf("All tests passed successfully.\n\n");

    return 0;
}


#endif //AS2_ARRAYLIST_TEST_H
