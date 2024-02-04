# C Standard Library README

This repository contains a custom C standard library developed to provide various data structures and utility functions commonly used in C programming. Below are the details of the available modules and the functions they provide.

## `array_list.h`

This module provides an implementation of a dynamic array list data structure.

### Functions

- `alist_new`: Create a new empty array list.
- `alist_new_init_size`: Create a new array list with an initial capacity.
- `alist_push_back`: Add an element to the end of the array list.
- `alist_nth`: Get the nth element from the array list.
- `alist_size`: Get the size of the array list.
- `alist_free_dangle`: Free memory allocated to the array list without freeing the elements.
- `alist_free`: Free memory allocated to the array list and its elements.
- `alist_remove_nth`: Remove the nth element from the array list.
- `alist_remove_front`: Remove the first element from the array list.
- `alist_remove_back`: Remove the last element from the array list.
- `alist_insert_nth`: Insert an element at the nth position in the array list.
- `alist_map`: Apply a function to each element of the array list.
- `alist_filter`: Filter elements of the array list based on a condition.
- `alist_foreach`: Apply a function to each element of the array list.

## `string_tokens.h`

This module provides functions for splitting strings into tokens.

### Functions

- `stok_split`: Split a string into tokens based on a delimiter.
- `stok_len`: Get the number of tokens in a string.
- `stok_nth`: Get the nth token from a string.
- `stok_to_array`: Convert tokens to an array of strings.

## Running Tests

To ensure the correctness of the library, unit tests have been provided for each module. The test files are named `test_array_list.c` and `test_string_tokens.c` respectively. These tests can be executed to verify that the functions are working as expected.

## Contributors

- Osebhulimen Egbor - osesegbor04@gmail.com

## License

This project is licensed under the [MIT License](LICENSE). Feel free to use and modify the code according to your needs. Contributions are welcome!
