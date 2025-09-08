// #include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pgetopt.h"
#include "lib/popt_tree.h"


pclass *pclass_create (pinit **init, char *name )
{    
    (*init)->classes = (struct object **) realloc ( (*init)->classes, ( sizeof (struct object *) * ((*init)->classes_index+1) ) );
    
    (*init)->classes[(*init)->classes_index]  = (struct object *) malloc (sizeof (struct object));
    (*init)->classes[(*init)->classes_index]->name = name;
    
    (*init)->classes[(*init)->classes_index]->alw_size = 0;
    (*init)->classes[(*init)->classes_index]->avl_size = 0;

    (*init)->classes[(*init)->classes_index]->alw_tree = NULL;
    (*init)->classes[(*init)->classes_index]->avl_tree = NULL;

    return (*init)->classes[(*init)->classes_index++];
}

void pclass_set_allowed_options ( pclass **class, palw *alw_opts )
{
    unsigned long int i = 0;

    while (alw_opts[i].option_name != NULL)
    {

        switch (alw_opts[i].option_mode)
        {
            case FLAG:
                (*class)->alw_tree = (struct branch **) realloc ( (*class)->alw_tree, ( sizeof (struct branch *) * ((*class)->alw_size + 1) ) );
                (*class)->alw_tree[(*class)->alw_size] = (struct branch *) malloc ( sizeof (struct branch));
                (*class)->alw_tree[(*class)->alw_size]->name = alw_opts[i].option_name;
                (*class)->alw_tree[(*class)->alw_size]->node_mode = FLAG;
                (*class)->alw_tree[(*class)->alw_size]->ID = alw_opts[i].ID;
                (*class)->alw_tree[(*class)->alw_size]->values_size = 0;
                (*class)->alw_tree[(*class)->alw_size]->values = NULL;
        }
        ++i;
        ++(*class)->alw_size;   // also i can write it : (*class)->alw_tree[(*class)->alw_size+i] and remove the ++(*class)->alw_size
                                // ++(*class)->alw_size from here, and put this line in the out of the while segment :
                                // (*class)->alw_size += i;
                                // But it compromises the readability of the code. No?
    }
}

int pclass_loop_get ( pclass  *class, unsigned int index )
{
    if ( index >= (class->avl_size))    return -1;
    return class->avl_tree[index]->ID;
}


void pclass_free ( pclass **class )
{
        for ( unsigned int i1 = 0 ; i1 < (*class)->alw_size ; ++i1 )
        {
            for ( unsigned int i2 = 0 ; i2 < (*class)->alw_tree[i1]->values_size ; ++i2 )
            {
                free ((*class)->alw_tree[i1]->values[i2]);
            }
            // free ((*class)->alw_tree[i1]->name); Dont Need to use this free function
            /* 
             * Since in the pclass_set_allowed_options function, the name field in the branch structure is assigned using the value passed 
             * as an argument to the function, there is no need to free it manually.
             * However, in the name field of the avl_tree array within the branch structure, memory is allocated manually using malloc, so 
             * it must be freed explicitly.
            */
            free ((*class)->alw_tree[i1]);
        }
        for ( unsigned int i1 = 0 ; i1 < (*class)->avl_size ; ++i1 )
        {
            for ( unsigned int i2 = 0 ; i2 < (*class)->avl_tree[i1]->values_size ; ++i2 )
            {
                free ((*class)->avl_tree[i1]->values[i2]);
            }
            free ((*class)->avl_tree[i1]->name);
            free ((*class)->avl_tree[i1]);
        }
        free ((*class)->alw_tree);
        free ((*class)->avl_tree);
        free (*class);
}