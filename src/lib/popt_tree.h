#include <stdbool.h>
#include <string.h>

#ifndef POPT_STRING
#define POPT_STRING

#include "pgetopt.h"

static optmod is_alw ( pclass *class, char *option )
{
    for ( int classI=0 ; classI < class->alw_size ; ++classI )
    {
        if ( strcmp (class->alw_tree[classI]->name, option) == 0 )
            return class->alw_tree[classI]->node_mode;
    }
    return -1;
}

static bool is_repetitive_flag ( pclass *class, char *option )
{
    for ( int i = 0 ; i < class->avl_size ; ++i )
    {
        if ( strcmp (class->avl_tree[i]->name, option) == 0 )
            {
                return true;
            }
    }
    return false;
}


#endif