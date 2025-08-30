#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lib/popt_string.h"
#include "pgetopt.h"

popt *popt_init (void)
{
    popt *root = (popt *) malloc (sizeof (popt));
    root->tree = (struct init **) malloc (sizeof (struct init *));

    root->avl_flags = (char**) malloc (sizeof (char *));

    root->flags_num = 0;
    root->avl_flags_num = 0;
    return root;
}

char *popt_parse ( popt **root, int argc, char *argv[] )
{
    char **flags= (char **) malloc (sizeof (char *));;
    int flags_number = pget_flags_list ( &flags, argc, argv );
    
    ((*root)->tree) = (struct init **) realloc (((*root)->tree), sizeof (struct init *)*(flags_number+1));
    (*root)->flags_num = flags_number;

    for ( unsigned long int i=0 ; i<flags_number ; ++i )
    {
        if ( is_flag_available ((**root), flags[i]) == false )
            return flags[i];
        ((*root)->tree)[i] = (struct init *) malloc (sizeof (struct init));
        ((*root)->tree)[i]->name = flags[i];
        ((*root)->tree)[i]->branches = NULL;
    }
    ////////////////////////////////////////////////////////////////

    
    free (flags);
    return NULL;
}


void pset_avl_opts ( popt **root, pavl *avl_opts )
{
    unsigned long int i = 0;

    while (avl_opts[i].opts != NULL)
    {
        switch (avl_opts[i].option_mode)
        {
            case flag:
                if ( strlen (avl_opts[i].opts) != 1) {printf ("ERROR in available flags list\n"); exit (0);}
                (*root)->avl_flags = (char **) realloc ((*root)->avl_flags, sizeof (char*)*((*root)->avl_flags_num+1));
                (*root)->avl_flags[(*root)->avl_flags_num] = avl_opts[i].opts;
                ++(*root)->avl_flags_num;
                break;
            case key:
                break;
        }
        ++i;
    }
}

void pfree ( popt **root )
{
    /* We must be free the all pointers :)
    */
    for ( int i = 0 ; i < ((*root)->flags_num + (*root)->keys_num) ; ++i )
    {
        free ((*root)->tree[i]->name);
        if ( (*root)->tree[i]->branches != NULL )
        {
            // printf ("This is a key : %s\n", (*root)->tree[i]->name);
        }
        free ((*root)->tree[i]);
    }
    free ((*root)->tree);
    free ((*root)->avl_flags);
    free (*root);
}