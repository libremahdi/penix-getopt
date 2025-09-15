#include <stdbool.h>
#include <string.h>

#ifndef POPT_STRING
#define POPT_STRING

#include "pgetopt.h"

static int is_alw ( pclass *class, char *option )
{
    for ( int classI=0 ; classI < class->alw_size ; ++classI )
    {
        if ( ( strcmp (class->alw_tree[classI]->name, option) == 0 ) && ( class->alw_tree[classI]->key_type != -1 ) )
            return -2; // 0 is reserved for flags, and -1 is reserved for errors.
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

static bool is_repetitive_ID ( pclass *class, unsigned int ID )
{
    for ( int i = 0 ; i < class->avl_size ; ++i )
        if ( class->avl_tree[i]->ID == ID )
            return true;
    return false;
}


static struct branch **get_point ( pclass *class, char *option )
{
    for ( int i = 0 ; i < class->avl_size ; ++i )
        if ( strcmp (class->avl_tree[i]->name, option) == 0 )
            return &class->avl_tree[i];
}

#endif