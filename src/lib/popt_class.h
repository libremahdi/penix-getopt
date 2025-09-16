#include <stdio.h>

#ifndef POPT_CLASS
#define POPT_CLASS

static unsigned int is_alw_tree_repetitive_id ( pclass *class, unsigned int opt_id )
{
    for ( int i = 0 ; i < class->alw_size ; ++i )
        if ( class->alw_tree[i]->opt_id == opt_id ) return i;
    return -1;
}

#endif