#include "pgetopt.h"
#include "lib/popt_class.h"
#include "lib/popt_error.h"
#include "salloc.h"

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

int pclass_loop_get_opt_id ( pclass  *class, unsigned int index )
{
    if ( index >= (class->avl_size) )    return -1;
    return class->avl_tree[index]->opt_id;
}


unsigned int pclass_get_key_size ( pclass  *class, unsigned int opt_id )
{
    for ( int classI=0 ; classI <  (class)->avl_size ; ++classI )
    {
        if ( (class)->avl_tree[classI]->opt_id == opt_id )
        {
            return (class)->avl_tree[classI]->values_size;
        }
    }
    char *err; sprintf (err, "No available key found under this opt_id: %d", opt_id); 
    /* The user may not have used any key, but you want to get the number of values of that key!
    */
    _printerr_pgetopt ( err, __LINE__, __FILE__ );
}


char *pclass_key_loop_get_value ( pclass  *class, unsigned int opt_id, unsigned int index )
{
    for ( int classI=0 ; classI <  (class)->avl_size ; ++classI )
    {
        if ( (class)->avl_tree[classI]->opt_id == opt_id )
        {
            return (class)->avl_tree[classI]->values[index];
        }
    }
    char *err; sprintf (err, "No available key found under this opt_id: %d", opt_id); 
    /* The user may not have used any key, but you want to get the values of that key!
    */
    _printerr_pgetopt ( err, __LINE__, __FILE__ );
}
