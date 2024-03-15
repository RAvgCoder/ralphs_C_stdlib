//
// Created by egbor on 2024-01-31.
//

#ifndef AS2_STDLIB_TESTS_H
#define AS2_STDLIB_TESTS_H


#include "string_tokens_test.h"
#include "arraylist_test.h"
#include "linked_list_test.h"
#include "../utils.h"

void stdlib_run_all_tests()
{

    alist_test_all();
    stok_test_all();
    l_list_test_all();
}

#endif //AS2_STDLIB_TESTS_H
