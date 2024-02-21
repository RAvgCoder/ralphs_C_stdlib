//
// Created by egbor on 2024-01-30.
//
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../string_tokens.h"
#include "../array_list.h"

typedef struct sTokens {
    array_list_t tokens;
} sTokens;

static sTokens *stok_init();

static void stok_add(sTokens *stok, char *token);

/**
 * Splits a string an returns an array of split strings
 * @param str: String to split
 * @param delim: What to split by
 */
string_tokens_t stok_split(char *str, char *delimeter) {
    sTokens *stok = stok_init();
    // Split the string
    char *dup = strdup(str);
    char *word = strtok(dup, delimeter);
    while (word != NULL) {
        // Removes extra new line at the end of the line
        if (word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0';
        }

        // Store word
        stok_add(stok, word);

        // Read in next word
        word = strtok(NULL, delimeter);
    }
    return stok;
}

/**
 *  Converts the tokens to a new array of tokens
 *  all strings are not duplicated to keep original refereces manually copy over using stok_nth()
 */
char **stok_to_array(string_tokens_t string_tokens) {
    int len = stok_len(string_tokens);
    // +1 is done so that the end of  the string is array is null
    char **arr = calloc(len + 1, sizeof(char *));
    for (int i = 0; i < len; i++) {
        char *tok = strdup(stok_nth(string_tokens, i));
        arr[i] = tok;
    }
    return arr;
}

/**
 * Gets how many words it was able to split into
 */
unsigned int stok_len(string_tokens_t string_tokens) {
    return alist_size(((sTokens *) string_tokens)->tokens);
}

/**
 * Gets the nth token returns NULL if index is invalid
 */
char *stok_nth(string_tokens_t string_tokens, int idx) {
    return (char *) alist_nth(((sTokens *) string_tokens)->tokens, idx);
}

/**
 * Frees the tokens created
 */
void stok_free(string_tokens_t string_tokens) {
   if (stok_len( string_tokens ) != 0) {
        char *line = alist_nth(((sTokens*)string_tokens)->tokens, 0);
        alist_free_dangle(((sTokens *) string_tokens)->tokens);
        free(line);
    }
}

/**
 * Creates a string token
 */
static sTokens *stok_init() {
    // Create a string token
    sTokens *stok = (sTokens *) malloc(sizeof(sTokens *));
    assert(stok && "Failed to allocate memory for string tokens");

    // Init struct members
    stok->tokens = alist_new();
    assert(stok->tokens && "Failed to alocate memeory for tokens list");

    return stok;
}

/**
 * Stores a token in the list of tokens
 */
static void stok_add(sTokens *stok, char *token) {
    // token = strdup(token);
    alist_push_back(stok->tokens, token);
}

