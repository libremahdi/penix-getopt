#include <stdio.h>
#include <string.h>


#include "pgetopt.h"
#include "lib/popt_class.h"

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
    printf ( "pclass_set_key ERROR:\nCant find Class with ID %d\n", opt_id );
    abort ();
}


unsigned int pkey_get_key_size ( pkey *key )
{
    return key->values_size;
}

void pkey_set_custom_value ( pkey **key, char *value )
{
    (*key)->values = ( char ** ) realloc ( (*key)->values , (sizeof (char *) * ((*key)->values_size+1) ) );
    (*key)->values[ ((*key)->values_size) ] = value;
    ++(*key)->values_size;
}

char *pkey_key_loop_get_value ( pkey *key, unsigned int index )
{
    if ( index < (key->values_size) )   return key->values[index];
    printf ( "pkey_key_loop_get_value ERROR:\nIndex %d is out of range. Valid indices are from 0 to %d.\n", index, key->values_size-1 );
    abort ();
}
