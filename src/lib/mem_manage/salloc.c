#include <stdlib.h>

void* salloc ( size_t size )
{
    void *ret_value = malloc ( size );
    if ( ret_value == NULL )    abort(); // This is a test code and will be modified later.

    return ret_value;
}