//
// Created by egbor on 2024-01-31.
//

#ifndef AS2_STRING_TOKENS_TEST_H
#define AS2_STRING_TOKENS_TEST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../string_tokens.h"
#include <assert.h>
#include "../utils.h"


/* Test function prototypes */
void test_stok_split();

void test_stok_len();

void test_stok_nth();

void test_stok_to_array();

void test_stok_free();

void stok_test_all()
{
    /* Run tests */
    printf("// ------- [ STRING TOKEN TEST ] ------- \\\\ \n");

    test_stok_split();
    test_stok_len();
    test_stok_nth();
    test_stok_to_array();
    test_stok_free();

    printf("All tests passed successfully.\n\n");
}

/* Test cases */
void test_stok_split()
{
    printf("Testing stok_split...\n");

    char str[] = "Hello,world,how,are,you";
    char delim[] = ",";
    string_tokens_t tokens = stok_split(str, delim);

    STDLIB_ASSERT(stok_len(tokens) == 5,
                  "Splitting 'Hello,world,how,are,you' by ',' doesn't result in 5 tokens being created")

    STDLIB_ASSERT(strcmp(stok_nth(tokens, 0), "Hello") == 0,
                  "First token doesn't match Having: %s, Expecting: %s", stok_nth(tokens, 0), "Hello")

    STDLIB_ASSERT(strcmp(stok_nth(tokens, 1), "world") == 0,
                  "Second token doesn't match Having: %s, Expecting: %s", stok_nth(tokens, 1), "world")

    STDLIB_ASSERT(strcmp(stok_nth(tokens, 2), "how") == 0,
                  "Third token doesn't match Having: %s, Expecting: %s", stok_nth(tokens, 2), "how")

    STDLIB_ASSERT(strcmp(stok_nth(tokens, 3), "are") == 0,
                  "Fourth token doesn't match Having: %s, Expecting: %s", stok_nth(tokens, 3), "are")

    STDLIB_ASSERT(strcmp(stok_nth(tokens, 4), "you") == 0,
                  "Fifth token doesn't match Having: %s, Expecting: %s", stok_nth(tokens, 4), "you")

    stok_free(tokens);
}

void test_stok_len()
{
    printf("Testing stok_len...\n");

    char str[] = "Hello,world,how,are,you";
    string_tokens_t tokens = stok_split(str, ",");
    string_tokens_t tokens1 = stok_split(str, " ");

    STDLIB_ASSERT(stok_len(tokens) == 5,
                  "Splitting 'Hello,world,how,are,you' by ',' doesn't result in 5 token being created it has %d",
                  stok_len(tokens))

    STDLIB_ASSERT(stok_len(tokens1) == 1,
                  "Splitting 'Hello,world,how,are,you' by ' ' doesn't result in 1 token being created it has %d",
                  stok_len(tokens))

    stok_free(tokens);
    stok_free(tokens1);
}

void test_stok_nth()
{
    printf("Testing stok_nth...\n");

    char str[] = "Hello,world,how,are,you";
    char delim[] = ",";
    string_tokens_t tokens = stok_split(str, delim);

    STDLIB_ASSERT(stok_len(tokens) == 5,
                  "Splitting 'Hello,world,how,are,you' by ',' doesn't result in 5 tokens being created")

    STDLIB_ASSERT(strcmp(stok_nth(tokens, 0), "Hello") == 0,
                  "First token doesn't match Having: %s, Expecting: %s", stok_nth(tokens, 0), "Hello")

    STDLIB_ASSERT(strcmp(stok_nth(tokens, 1), "world") == 0,
                  "Second token doesn't match Having: %s, Expecting: %s", stok_nth(tokens, 1), "world")

    STDLIB_ASSERT(strcmp(stok_nth(tokens, 2), "how") == 0,
                  "Third token doesn't match Having: %s, Expecting: %s", stok_nth(tokens, 2), "how")

    STDLIB_ASSERT(strcmp(stok_nth(tokens, 3), "are") == 0,
                  "Fourth token doesn't match Having: %s, Expecting: %s", stok_nth(tokens, 3), "are")

    STDLIB_ASSERT(strcmp(stok_nth(tokens, 4), "you") == 0,
                  "Fifth token doesn't match Having: %s, Expecting: %s", stok_nth(tokens, 4), "you")


    stok_free(tokens);
}

void test_stok_to_array()
{
    printf("Testing stok_to_array...\n");

    char str[] = "Hello,world,how,are,you";
    char delim[] = ",";
    string_tokens_t tokens = stok_split(str, delim);

    char **arr = stok_to_array(tokens);
    for (int i = 0; i < stok_len(tokens); ++i)
    {
        STDLIB_ASSERT(strcmp(arr[i], stok_nth(tokens, i)) == 0,
                      "Error when checking split string to char array Having: %s, Expected: %s", stok_nth(tokens, i),
                      arr[i])
    }

    stok_free(tokens);
    free(arr);
}

void test_stok_free()
{
    printf("Testing stok_free...\n");

    const char *source = "Hello,world,how,are,you";

    // Calculate the length of the string
    size_t length = strlen(source);

    // Allocate memory for the string plus one extra byte for the null terminator
    char *destination = (char *) malloc(length + 1);

    // Check if memory allocation was successful
    if (destination == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Copy the string into the allocated memory
    strcpy(destination, source);
    char delim[] = ",";
    string_tokens_t tokens = stok_split(destination, delim);

    free(destination);
    stok_free(tokens);
}

#endif //AS2_STRING_TOKENS_TEST_H
