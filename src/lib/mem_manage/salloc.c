#ifndef SALLOC__HEADER__
#define SALLOC__HEADER__

#include <stdlib.h>
#include <stdio.h>

#include "../popt_error.h"

void* salloc ( size_t size )
{
    void *ret_value = malloc ( size );
    if ( ret_value == NULL ) {
        _mem_alloc_fail (__LINE__, __FILE__);
        abort(); // This is a test code and will be modified later.
    }
    
    return ret_value;
}

#endif /* SALLOC__HEADER__ */