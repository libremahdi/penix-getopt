#include <stdio.h>
#include <string.h>

#include "pgetopt.h"

#ifndef POPT_INIT
#define POPT_INIT

static unsigned int is_avl_tree_repetitive_id ( pclass *class, unsigned int opt_id )
{
    for ( int i = 0 ; i < class->avl_size ; ++i )
        if ( class->avl_tree[i]->opt_id == opt_id ) return i;
    return -1;
}

static int get_id ( pclass *class, char *option )
{
    for ( int classI=0 ; classI < class->alw_size ; ++classI )
    {
        for ( int valueI=0 ; valueI < class->alw_tree[classI]->names_size ; ++valueI )
        {
            if ( strcmp ( class->alw_tree[classI]->names[valueI], option) == 0 )
            {
                return class->alw_tree[classI]->opt_id;
            }
        }
    }
    return -1;
}

static enum PKEY_TYPE get_key_type ( pclass *class, int opt_id )
{
    for ( int i = 0 ; i < class->alw_size ; ++i )
        if ( class->alw_tree[i]->opt_id == opt_id ) return class->alw_tree[i]->key_type;
}

#endif