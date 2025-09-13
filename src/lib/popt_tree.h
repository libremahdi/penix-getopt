#include <stdbool.h>
#include <string.h>

#ifndef POPT_STRING
#define POPT_STRING

#include "pgetopt.h"

static unsigned int is_alw ( pclass *class, char *option )
{
    for ( int classI=0 ; classI < class->alw_size ; ++classI )
    {
        if ( strcmp (class->alw_tree[classI]->name, option) == 0 )
            return class->alw_tree[classI]->values_size;
    }
    return -1;
}

static unsigned int what_is_ID ( pclass *class, char *option )
{
    for ( int classI=0 ; classI < class->alw_size ; ++classI )
    {
        if ( strcmp (class->alw_tree[classI]->name, option) == 0 )
            return class->alw_tree[classI]->ID;
    }
}

static bool is_repetitive ( pclass *class, char *option )
{
    for ( int i = 0 ; i < class->avl_size ; ++i )
        if ( strcmp (class->avl_tree[i]->name, option) == 0 )
                return true;
    return false;
}

static struct branch *get_point ( pclass *class, char *option )
{
    for ( int i = 0 ; i < class->avl_size ; ++i )
        if ( strcmp (class->avl_tree[i]->name, option) == 0 )
            return class->avl_tree[i];
}

#endif