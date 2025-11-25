#include "pgetopt.h"

int pclass_loop_get_opt_id ( pclass  *class, unsigned int index )
{
    if ( index >= (class->avl_size) )    return -1;
    return class->avl_tree[index]->opt_id;
}