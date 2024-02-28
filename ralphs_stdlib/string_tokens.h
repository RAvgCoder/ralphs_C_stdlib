//
// Created by egbor on 2024-01-30.
//
#pragma once

#include <stdlib.h>
#include <assert.h>
typedef void* string_tokens_t;

/**
 * Splits a string an returns an array of split strings
 * @param str: String to split
 * @param delim: What to split by
 */
extern string_tokens_t stok_split(char* str, char* delimiter);

/**
 *  Gets how many words it was able to split into
 */
extern unsigned int stok_len(string_tokens_t string_tokens);

/**
 * Frees the tokens created
 */
extern void stok_free(string_tokens_t string_tokens);

/**
 * Gets the nth token returns NULL if index is invalid
 */
extern char* stok_nth(string_tokens_t string_tokens, int idx);

/**
 *  Converts the tokens to a new array of tokens all strings are not
 *  duplicated to keep original references manually copy over using stok_nth()
 */
extern char** stok_to_array(string_tokens_t string_tokens);
