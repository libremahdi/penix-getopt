#include "pgetopt.h"
#include "salloc.h"

void pinit_set_allowed_masters ( pinit **init, palw *allowed_names )
{
    unsigned long int i = 0;
    while ( allowed_names[i].option_name != NULL )
    {
        (*init)->alw_masters = ( struct master_alw ** ) realloc ( (*init)->alw_masters , ( sizeof ( struct master_alw * ) * ((*init)->alw_masters_size+1) ) );
        (*init)->alw_masters [ (*init)->alw_masters_size ] = salloc ( sizeof ( struct master_alw ) );
        (*init)->alw_masters [ (*init)->alw_masters_size ] -> name = allowed_names[i].option_name;
        (*init)->alw_masters [ (*init)->alw_masters_size ] -> master_id = allowed_names[i].option_id;
        ++i;
        ++(*init)->alw_masters_size;
    }
}