**README for Custom C Library**

---

**Overview**

This README provides documentation for a custom C library containing two modules: `array_list` and `string_tokens`. This library is part of a mini stdlib being developed for C programming.

**Module: array_list**

The `array_list` module provides functionalities for creating and manipulating dynamic arrays.


- **`alist_new()`**
    - Creates a new array list.
- **`alist_new_init_size(int initial_capacity)`**
    - Creates a new array list with a specified initial capacity.
- **`alist_push_back(array_list_t array_list, void* item)`**
    - Adds an element to the back of the array list.
- **`alist_nth(array_list_t array_list, int idx)`**
    - Retrieves the nth element from the array list.
- **`alist_size(array_list_t array_list)`**
    - Returns the size of the array list.
- **`alist_free_dangle(array_list_t array_list)`**
    - Deletes the array list without deallocating its elements (high risk of memory leaks).
- **`alist_free(array_list_t array_list)`**
    - Deletes the array list and deallocates all its elements.
- **`alist_remove_nth(array_list_t array_list, int idx)`**
    - Removes a value from a specified index in the array list and returns the value if found.
- **`alist_remove_front(array_list_t array_list)`**
    - Removes the first element from the array list.
- **`alist_remove_back(array_list_t array_list)`**
    - Removes the last element from the array list.
- **`alist_insert_nth(array_list_t array_list, void* item, int idx)`**
    - Inserts an element at a specified index in the array list.
- **`alist_map(array_list_t array_list, void* (*map_function)(const void*))`**
    - Applies a function to each element of the array list.
- **`alist_filter(array_list_t array_list, bool (*filter_function)(const void*))`**
    - Filters elements of the array list based on a condition.
- **`alist_foreach(array_list_t array_list, void (*foreach_function)(void*))`**
    - Applies a function to each element of the array list.

**Module: string_tokens**

The `string_tokens` module provides functionalities for splitting strings into tokens.

- **`stok_split(char* str, char* delimiter)`**
    - Splits a string into an array of tokens based on a specified delimiter.
- **`stok_len(string_tokens_t string_tokens)`**
    - Returns the number of tokens in the token array.
- **`stok_free(string_tokens_t string_tokens)`**
    - Frees the memory allocated for the token array.
- **`stok_nth(string_tokens_t string_tokens, int idx)`**
    - Retrieves the nth token from the token array.
- **`stok_to_array(string_tokens_t string_tokens)`**
    - Converts the tokens to a new array of tokens (original references are not duplicated).

**Note:**

This library is a custom implementation intended for educational and experimental purposes. It is not a full-fledged replacement for standard libraries and may not be as robust or efficient as established libraries.

**Author:**
Osebhulimen Egbor

---
