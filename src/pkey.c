#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pgetopt.h"
#include "lib/popt_key.h"

void pkey_custom_set_value ( pkey *KEY, char *value )
{
    if ( ((*KEY)->key_type != ALW_CUSTOM) && ((*KEY)->key_type != DENY_CUSTOM) )
    {
        printf ( "ERROR: `%s` is not a custom key\n", (*KEY)->name );
        abort ();
    }
    (*KEY)->values = ( char ** ) realloc ( (*KEY)->values , (sizeof (char *) * ((*KEY)->values_size+1) ) );
    (*KEY)->values[ ((*KEY)->values_size) ] = value;
    ++(*KEY)->values_size;
}

