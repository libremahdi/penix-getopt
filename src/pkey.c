
#include "pgetopt.h"
#include "lib/popt_class.h"
#include "lib/popt_error.h"

pkey *pclass_set_key ( pclass **class, unsigned int opt_id, enum PKEY_TYPE key_type )
{
    for ( int classI = 0 ; classI < (*class)->alw_size ; ++classI )
    {
        if ( (*class)->alw_tree[classI]->opt_id == opt_id )
        {
            (*class)->alw_tree[classI]->key_type = key_type;
            return (*class)->alw_tree[classI];
        }
    }
    char *err; sprintf (err, "No opt_id with number %d was found to convert it to kay", opt_id); 
    /* This error is issued when you want to set an option to key but such an opt_id is not found.
    */
    _printerr_pgetopt ( err, __LINE__, __FILE__ );
}

void pkey_set_custom_value ( pkey **key, char *value )
{
    (*key)->values = ( char ** ) realloc ( (*key)->values , (sizeof (char *) * ((*key)->values_size+1) ) );
    (*key)->values[ ((*key)->values_size) ] = value;
    ++(*key)->values_size;
}