#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lib/popt_string.h"
#include "pgetopt.h"

popt *popt_init (void)
{
    popt *root = (popt *) malloc (sizeof (popt));
    root->tree = (struct init **) malloc (sizeof (struct init *));

    root->avl_flags = (char**) malloc (sizeof (char *));
    // root->avl_keys  = (char**) malloc (sizeof (char *));

    root->flags_num = 0;
    root->keys_num  = 0;
    return root;
}

int popt_parse ( popt **root, int argc, char *argv[] )
{
    char **flags;
    int flags_number = pget_flags_list ( &flags, argc, argv );
    
    ((*root)->tree) = (struct init **) realloc (((*root)->tree), sizeof (struct init *)*flags_number);
    for ( unsigned long int i=0 ; i<flags_number ; ++i )
    {
        ((*root)->tree)[i] = (struct init *) malloc (sizeof (struct init));
        ((*root)->tree)[i]->name = (char*) malloc (sizeof (char));
        ((*root)->tree)[i]->name = flags[i];
        ((*root)->tree)[i]->branches = NULL;
    }

    // (*root)->avl_flags = (char **) realloc ((*root)->avl_flags, sizeof (char *)*flags_number);
    // (*root)->flags_num = flags_number;
    // (*root)->avl_flags = flags;


}

void pfree ( popt **root )
{
    /* We must be free the all pointers :)
    */
    for ( int i = 0 ; i < (*root)->flags_num ; ++i )
        free ((*root)->avl_flags[i]);
    free ((*root)->avl_flags);
}