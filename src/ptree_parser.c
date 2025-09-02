#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "lib/popt_string.h"
#include "pgetopt.h"

void pclass_create (popt **init, char *name )
{    
    (*init)->classes = (struct object **) realloc ( (*init)->classes, ( sizeof (struct object *) * ((*init)->class_size+1) ) );
    
    (*init)->classes[(*init)->class_size]  = (struct object *) malloc (sizeof (struct object));
    (*init)->classes[(*init)->class_size]->name = name;
    
    (*init)->classes[(*init)->class_size]->alw_size = 0;
    (*init)->classes[(*init)->class_size]->avl_size = 0;

    (*init)->classes[(*init)->class_size]->alw_tree = NULL;
    (*init)->classes[(*init)->class_size]->avl_tree = NULL;

    ++(*init)->class_size;
}

popt *popt_init (void)
{
    popt *init          = (popt *) malloc (sizeof (popt));
    init->class_size    = 0;
    init->classes       = NULL;
    pclass_create (&init, "main");
    return init;
}

void pfree ( popt **init )
{
    for ( unsigned int i0 = 0 ; i0<((*init)->class_size) ; ++i0 )
    {
        for ( unsigned int i1 = 0 ; i1 < (*init)->classes[i0]->alw_size ; ++i1 )
        {
            for ( unsigned int i2 = 0 ; i2 < (*init)->classes[i0]->alw_tree[i1]->values_size ; ++i2 )
            {
                free ((*init)->classes[i0]->alw_tree[i1]->values[i2]);
            }
        }
        for ( unsigned int i1 = 0 ; i1 < (*init)->classes[i0]->avl_size ; ++i1 )
        {
            for ( unsigned int i2 = 0 ; i2 < (*init)->classes[i0]->avl_tree[i1]->values_size ; ++i2 )
            {
                free ((*init)->classes[i0]->avl_tree[i1]->values[i2]);
            }
        }
        free ((*init)->classes[i0]->alw_tree);
        free ((*init)->classes[i0]->avl_tree);
        free ((*init)->classes[i0]);
    }
    free ((*init)->classes);
    free ((*init));
}