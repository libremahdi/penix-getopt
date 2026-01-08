#ifndef PGETOPT__SALLOC
#define PGETOPT__SALLOC

#include <stdlib.h>
#include <stdio.h>
#include "popt_error.h"

void* pgetopt_alloc (size_t size) {
    void *ret_value = malloc (size);
    if (ret_value == NULL) {
        _mem_alloc_fail (__LINE__, __FILE__);
        abort();
    }
    return ret_value;
}

void *pgetopt_realloc (void *ptr, size_t size) {
    void *ret_value = realloc (ptr, size);
    if (ret_value == NULL) {
        _mem_alloc_fail (__LINE__, __FILE__);
        abort();
    }
    return ret_value;
}

#endif /* PGETOPT__SALLOC */