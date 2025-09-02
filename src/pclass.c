#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pgetopt.h"



pclass *pclass_create (popt **init, char *name )
{    
    (*init)->classes = (struct object **) realloc ( (*init)->classes, ( sizeof (struct object *) * ((*init)->class_size+1) ) );
    
    (*init)->classes[(*init)->class_size]  = (struct object *) malloc (sizeof (struct object));
    (*init)->classes[(*init)->class_size]->name = name;
    
    (*init)->classes[(*init)->class_size]->alw_size = 0;
    (*init)->classes[(*init)->class_size]->avl_size = 0;

    (*init)->classes[(*init)->class_size]->alw_tree = NULL;
    (*init)->classes[(*init)->class_size]->avl_tree = NULL;

    return (*init)->classes[(*init)->class_size++];
}

void pclass_free ( pclass **class )
{
        for ( unsigned int i1 = 0 ; i1 < (*class)->alw_size ; ++i1 )
        {
            for ( unsigned int i2 = 0 ; i2 < (*class)->alw_tree[i1]->values_size ; ++i2 )
            {
                free ((*class)->alw_tree[i1]->values[i2]);
            }
        }
        for ( unsigned int i1 = 0 ; i1 < (*class)->avl_size ; ++i1 )
        {
            for ( unsigned int i2 = 0 ; i2 < (*class)->avl_tree[i1]->values_size ; ++i2 )
            {
                free ((*class)->avl_tree[i1]->values[i2]);
            }
        }
        free ((*class)->alw_tree);
        free ((*class)->avl_tree);
        free (*class);
}