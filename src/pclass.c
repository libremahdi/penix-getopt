#include <stdio.h>
#include <string.h>


#include "pgetopt.h"
#include "lib/popt_class.h"

pclass *pclass_create ( pinit **init, char *name )
{    
    (*init)->classes = (struct class **) realloc ( (*init)->classes, ( sizeof (struct class *) * ((*init)->classes_size+1) ) );

    (*init)->classes[(*init)->classes_size]  = (struct class *) malloc (sizeof (struct class));
    (*init)->classes[(*init)->classes_size]->name = name;
    
    (*init)->classes[(*init)->classes_size]->alw_size = 0;
    (*init)->classes[(*init)->classes_size]->avl_size = 0;

    (*init)->classes[(*init)->classes_size]->alw_tree = NULL;
    (*init)->classes[(*init)->classes_size]->avl_tree = NULL;

    return (*init)->classes[(*init)->classes_size++];
}

void pclass_set_allowed_options ( pclass **class, palw *allowed_options )

{   unsigned long int i = 0;
    unsigned int repetitive_opt_id = 0;

    while (allowed_options[i].option_name != NULL)
    {
        if ( ( repetitive_opt_id = is_alw_tree_repetitive_id ( (*class), allowed_options[i].option_id ) ) != -1 )
        {
            (*class)->alw_tree[repetitive_opt_id]->names = ( char ** ) realloc ( ( (*class)->alw_tree[repetitive_opt_id]->names ) , ( sizeof (char *) * ( (*class)->alw_tree[repetitive_opt_id]->names_size + 1) ) );
            (*class)->alw_tree[repetitive_opt_id]->names[(*class)->alw_tree[repetitive_opt_id]->names_size] = allowed_options[i].option_name;
            ++(*class)->alw_tree[repetitive_opt_id]->names_size;
            ++i;
            continue;
        }
        (*class)->alw_tree = (struct alw_branch **) realloc ( (*class)->alw_tree, ( sizeof (struct alw_branch *) * ((*class)->alw_size + 1) ) );
        (*class)->alw_tree[(*class)->alw_size] = (struct alw_branch *) malloc ( sizeof (struct alw_branch));

        (*class)->alw_tree[(*class)->alw_size]->names = ( char ** ) malloc ( sizeof (char *) );
        (*class)->alw_tree[(*class)->alw_size]->names[0] = allowed_options[i].option_name;
        (*class)->alw_tree[(*class)->alw_size]->names_size = 1;

        (*class)->alw_tree[(*class)->alw_size]->opt_id = allowed_options[i].option_id;

        (*class)->alw_tree[(*class)->alw_size]->key_type = VOID;

        (*class)->alw_tree[(*class)->alw_size]->values_size = 0;
        (*class)->alw_tree[(*class)->alw_size]->values = NULL;
        ++i;
        ++(*class)->alw_size;   // also i can write it : (*class)->alw_tree[(*class)->alw_size+i] and remove the ++(*class)->alw_size
                                // ++(*class)->alw_size from here, and put this line in the out of the while segment :
                                // (*class)->alw_size += i;
                                // But it compromises the readability of the code. No?
    }
}

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

int pclass_loop_get_id ( pclass  *class, unsigned int index )
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
    printf ("ERROR: cant find `%d` key in avl options\n", opt_id);
    abort ();
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
    printf ("ERROR: cant find `%d` key in avl options\n", opt_id);
    abort ();
}
