/*
 *  Copyright (C) 2025-2026 Mahdi Hosseini Asaad
 *  For more information, please read LICENSE file.
 *
*/

#ifndef PGETOPT__SALLOC
#define PGETOPT__SALLOC

#include <stdlib.h>
#include <stdio.h>
#include "popt_error.h"

void* pgetopt__alloc (size_t size) {
    void *ret_value = malloc (size);
    if (ret_value == NULL) {
        pgetopt__mem_alloc_fail (__LINE__, __FILE__);
        abort();
    }
    return ret_value;
}

void *pgetopt__realloc (void *ptr, size_t size) {
    void *ret_value = realloc (ptr, size);
    if (ret_value == NULL) {
        pgetopt__mem_alloc_fail (__LINE__, __FILE__);
        abort();
    }
    return ret_value;
}

#endif /* PGETOPT__SALLOC */
