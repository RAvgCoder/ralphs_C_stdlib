//
// Created by egbor on 2024-03-13.
//

#ifndef ASS4_UTILS_H
#define ASS4_UTILS_H
#include <stdio.h>
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
 * STDLIB_ASSERT(strcmp(stok_nth(tokens, 0), "Hello") == 0,
 *             "First token doesn't match. Having: %s, Expecting: %s", stok_nth(tokens, 0), "Hello");
 * ```
 */
#define STDLIB_ASSERT(condition, ...) \
    if (!(condition)) { \
        printf("\n");   \
        fprintf(stderr, __VA_ARGS__);   \
        printf("\n");   \
        fprintf(stderr, "Assertion failed at %s:%d\n\n", __FILE__, __LINE__); \
        exit(EXIT_FAILURE); \
    }

/**
 * Calculates the modules of a number
 * mod(−a,b) = b − mod(a,b)
 * mod(a,b) = a % b
 *
 * @param a
 * @param b
 * @return The result
 */
#define STDLIB_MOD(a__, b__) \
    (((a__) < 0)   ?   ((b__) - (((-1 * (a__)) % (b__)))) \
                    :   ((a__) % (b__)))

#endif //ASS4_UTILS_H
