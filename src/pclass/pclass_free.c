#include "pgetopt.h"

void pclass_free ( pclass **class )
{
    // ALW Frees
    for ( int i = 0 ; i < (*class)->alw_size ; ++i )
    {
        free ((*class)->alw_tree[i]->names);
        free ((*class)->alw_tree[i]->values);
        free ((*class)->alw_tree[i]);
    }
    free ( (*class)->alw_tree );

    // AVL Frees
    for ( int i = 0 ; i < (*class)->avl_size ; ++i )
    {
        free ((*class)->avl_tree[i]->values);
        free ((*class)->avl_tree[i]);
    }
    free ( (*class)->avl_tree );
    free ((*class));
}