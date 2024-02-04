//
// Created by egbor on 2024-01-31.
//

#ifndef AS2_STDLIB_TESTS_H
#define AS2_STDLIB_TESTS_H

/**
 * Custom assertion macro.
 *
 * This macro checks if a condition is true. If the condition evaluates to false,
 * it prints an error message along with the file name and line number where the assertion failed,
 * and exits the program with EXIT_FAILURE.
 *
 * @param condition The condition to check.
 * @param ... Additional arguments for formatting the error message using printf-style formatting.
 *            These arguments are optional.
 *
 * Example usage:
 * ```
 * TEST_ASSERT(strcmp(stok_nth(tokens, 0), "Hello") == 0,
 *             "First token doesn't match. Having: %s, Expecting: %s", stok_nth(tokens, 0), "Hello");
 * ```
 */
#define TEST_ASSERT(condition, ...) \
    if (!(condition)) { \
        printf("\n");   \
        fprintf(stderr, __VA_ARGS__);   \
        printf("\n");   \
        fprintf(stderr, "Assertion failed at %s:%d\n\n", __FILE__, __LINE__); \
        exit(EXIT_FAILURE); \
    }


#include "string_tokens_test.h"
#include "arraylist_test.h"

void stdlib_run_all_tests() {

    alist_test_all();
    stok_test_all();
}

#endif //AS2_STDLIB_TESTS_H
