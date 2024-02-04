//
// Created by egbor on 2024-01-31.
//

#ifndef AS2_ARRAYLIST_TEST_H
#define AS2_ARRAYLIST_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../array_list.h"

/* Test function prototypes */
void test_alist_new();

void test_alist_new_init_size();

void test_alist_push_back();

void test_alist_nth();

void test_alist_size();

void test_alist_free_dangle();

void test_alist_free();

void test_alist_remove_nth();

void test_alist_remove_front();

void test_alist_remove_back();

void test_alist_insert_nth();

void test_alist_map();

void *map_x10_helper(const void *int_data);

void test_alist_filter();

bool filter_mod2_helper(const void *int_data);

void test_alist_foreach();

void foreach_x10_helper(void *int_data);

int alist_test_all() {
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


    printf("All tests passed successfully.\n\n");

    return 0;
}

/* Test cases */
void test_alist_new() {
    printf("Testing alist_new...\n");
    array_list_t list = alist_new();
    TEST_ASSERT(list != NULL, "List created was null and expected non-NULL")
    alist_free_dangle(list);
}

void test_alist_new_init_size() {
    printf("Testing alist_new_init_size...\n");
    int init_size = 21;
    array_list_t list = alist_new_init_size(init_size);
    array_list_t list1 = alist_new();

    // Checks the pointer offset where it expects max_capacity(PADDING USED) to be
    int PADDING = *((int *) (list1 + sizeof(void *) + sizeof(int)));
    init_size = ((init_size + PADDING) / PADDING) * PADDING; // 30

    int size = *((int *) (list + sizeof(void *) + sizeof(int)));

    TEST_ASSERT(size == init_size,
                "Size of max capacity is not set Expected: %d, Gotten: %d", init_size, size)

    alist_free_dangle(list);
    alist_free_dangle(list1);

}

void test_alist_push_back() {
    printf("Testing alist_push_back...\n");
    array_list_t list = alist_new();

    size_t data1 = 10;
    alist_push_back(list, &data1);
    TEST_ASSERT(alist_size(list) == 1,
                "Expected num of elements in the array to be 1 but found %zu", alist_size(list))

    size_t gotten = *(size_t *) alist_nth(list, 0);
    TEST_ASSERT(gotten == data1,
                "Value gotten from the array was %zu but got %zu", data1, gotten)

    alist_free_dangle(list);
}

void test_alist_nth() {
    printf("Testing alist_nth...\n");
    array_list_t list = alist_new();

    int data1 = 10;
    alist_push_back(list, &data1);

    TEST_ASSERT(alist_nth(list, 0) != NULL,
                "Data gotten at index 0 is expected to be non-null")
    TEST_ASSERT(alist_nth(list, -1) == NULL,
                "Data gotten at index 0 is expected to be null")

    int gotten = *(int *) alist_nth(list, 0);
    TEST_ASSERT(gotten == data1,
                "Data gotten seems to not match expected Gotten: %d, Expected %d", gotten, data1)

    alist_free_dangle(list);
}

void test_alist_size() {
    printf("Testing alist_size...\n");
    array_list_t list = alist_new();

    int data1 = 10;
    alist_push_back(list, &data1);
    TEST_ASSERT(alist_size(list) == 1,
                "Pushed only one element but but size reported says %zu", alist_size(list))

    alist_free_dangle(list);
}

void test_alist_free_dangle() {
    printf("Testing alist_free_dangle...\n");
    array_list_t list = alist_new();
    alist_free_dangle(list); // Just to ensure no crashes
}

void test_alist_free() {
    printf("Testing alist_free...\n");
    array_list_t list = alist_new();

    int *ptr = (int *) calloc(10, sizeof(int));
    alist_push_back(list, ptr);
    alist_free(list); // Ensure no memory leaks
    alist_free(NULL); // Ensure no free of NULL values
}

void test_alist_remove_nth() {
    printf("Testing alist_remove_nth...\n");
    array_list_t list = alist_new();

    int data1 = 10;
    alist_push_back(list, &data1);
    TEST_ASSERT(alist_remove_nth(list, 0) != NULL,
                "Removing a valid element at a valid index zero, returns NULL but was expecting NOT-NULL")

    TEST_ASSERT(alist_size(list) == 0,
                "Size after removal is expected to be zero but was %zu", alist_size(list))

    alist_free_dangle(list);
}

void test_alist_remove_front() {
    printf("Testing alist_remove_front...\n");
    array_list_t list = alist_new();

    int first = 0;
    int second = 1;
    alist_push_back(list, &first);
    alist_push_back(list, &second);

    alist_remove_front(list);

    int gotten = *((int *) alist_nth(list, 0));
    TEST_ASSERT(gotten == second,
                "Removing from the front of the list failed Expected %d, Got %d", second, gotten)

    alist_free_dangle(list);

}

void test_alist_remove_back() {
    printf("Testing alist_remove_back...\n");
    array_list_t list = alist_new();

    int first = 0;
    int second = 1;
    alist_push_back(list, &first);
    alist_push_back(list, &second);

    alist_remove_back(list);

    int *gotten = alist_nth(list, 1);
    TEST_ASSERT(gotten == NULL,
                "Removing from the front of the list failed Expected NULL, Got %d", *gotten)

    alist_free_dangle(list);
}

void test_alist_insert_nth() {
    printf("Testing alist_insert_nth...\n");
    array_list_t list = alist_new();

    int first = 1;
    int second = 2;
    int third = 3;
    alist_push_back(list, &first);
    alist_push_back(list, &third);

    alist_insert_nth(list, &second, 1);

    int gotten = *((int *) alist_nth(list, 1));
    TEST_ASSERT(gotten == second,
                "Inserting into the list failed Expected %d to be at the position of insertion, but got %d", second,
                gotten)

    alist_free_dangle(list);
}

void test_alist_map() {
    printf("Testing alist_map...\n");
    array_list_t list = alist_new();
    int MAX_ITER = 10;

    for (int i = 0; i < MAX_ITER; i++) {
        int *x = malloc(sizeof(int));
        assert(x && "Could not create data for mapping");
        *x = i;
        alist_push_back(list, x);
    }

    array_list_t mapped_list = alist_map(list, map_x10_helper);

    for (int i = 0; i < MAX_ITER; ++i) {
        int n = *(int *) alist_nth(mapped_list, i);
        TEST_ASSERT(n == (i * 10),
                    "Mapping failed Expected  %d, but Got: %d", (i * 10), n)
    }

    alist_free(list);
    alist_free(mapped_list);
}

void *map_x10_helper(const void *int_data) {
    int *mapped = malloc(sizeof(int));
    assert(mapped && "Could not create data for re-mapping");
    *mapped = *((int *) int_data) * 10;
    return mapped;
}

void test_alist_filter() {
    printf("Testing alist_filter...\n");
    array_list_t list = alist_new();
    int MAX_ITER = 10;

    for (int i = 0; i < MAX_ITER; i++) {
        int *x = malloc(sizeof(int));
        assert(x && "Could not create data for mapping");
        *x = i;
        alist_push_back(list, x);
    }

    array_list_t filtered_list = alist_filter(list, filter_mod2_helper);

    TEST_ASSERT(alist_size(filtered_list) == (size_t) (MAX_ITER / 2),
                "Filtered data size doesnt match Expected: %d, Got: %zu", (MAX_ITER / 2), alist_size(filtered_list))

    int i = 0;
    for (int mod_check = 0; mod_check < MAX_ITER; mod_check += 2) {
        int n = *(int *) alist_nth(filtered_list, i);

        TEST_ASSERT(n == mod_check,
                    "Mapping failed Expected  %d, but Got: %d", mod_check, n)

        i++;
    }

    alist_free(list);
    alist_free_dangle(filtered_list);
}

bool filter_mod2_helper(const void *int_data) {
    return (*((int *) int_data) % 2) == 0;
}

void test_alist_foreach() {
    printf("Testing alist_foreach...\n");
    array_list_t list = alist_new();
    int MAX_ITER = 10;

    for (int i = 0; i < MAX_ITER; i++) {
        int *x = malloc(sizeof(int));
        assert(x && "Could not create data for mapping");
        *x = i;
        alist_push_back(list, x);
    }

    alist_foreach(list, foreach_x10_helper);

    for (int i = 0; i < MAX_ITER; ++i) {
        int n = *(int *) alist_nth(list, i);
        int x = i;
        foreach_x10_helper(&x);
        TEST_ASSERT(n == x,
                    "Foreach function Expects output %d, but got %d", x, n);
    }

    alist_free(list);
}

void foreach_x10_helper(void *int_data) {
    *((int *) int_data) *= 10;
}

#endif //AS2_ARRAYLIST_TEST_H
