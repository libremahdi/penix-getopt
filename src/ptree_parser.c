#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "lib/popt_string.h"
#include "pgetopt.h"


/* alw_tree avl_tree Manual
 * this is Example code for understanding how the tree work!
    
    root->alw_tree      = (struct init **) realloc (root->alw_tree, sizeof (struct init *)*(SIZE_OF_LIST+1));
    root->alw_tree[0]   = (struct init *) malloc (sizeof (struct init));
    (root->alw_tree[0])->name = (char *) malloc (sizeof (char)*10);
    (root->alw_tree[0])->name = "Mahdi";
    (root->alw_tree[0])->node_mode = PFLAG;
    (root->alw_tree[0])->branches = NULL; 
    root->alw_tree[1]   = NULL;

*/
popt *popt_init (void)
{
    popt *root          = (popt *) malloc (sizeof (popt));
    
    root->alw_tree      = (struct init **) malloc (sizeof (struct init *));
    root->alw_size      = 1;
    root->avl_tree      = (struct init **) malloc (sizeof (struct init *));
    root->avl_size      = 1;
    return root;
}


/*
    root->alw_tree[0]   = (struct init *) malloc (sizeof (struct init));
    (root->alw_tree[0])->name = (char *) malloc (sizeof (char)*10);
    (root->alw_tree[0])->name = "Mahdi";
    (root->alw_tree[0])->node_mode = PFLAG;
    (root->alw_tree[0])->branches = NULL; 
    root->alw_tree[1]   = NULL;
*/
void pset_alw_opts   ( popt **root, palw *alw_opts )
{
    unsigned int i = 0;

    while (alw_opts[i].option_name != NULL)
    {
        (*root)->alw_tree[(*root)->alw_size-1] = (struct init *) malloc (sizeof (struct init));
        switch (alw_opts[i].option_mode)
        {
            case FLAG:
                // printf ("KEY : %s\n", alw_opts[i].option_name);
                (*root)->alw_tree[(*root)->alw_size-1]->name = alw_opts[i].option_name;
                (*root)->alw_tree[(*root)->alw_size-1]->node_mode = PFLAG;
                (*root)->alw_tree[(*root)->alw_size-1]->branches = NULL;
                break;
            case KEY:
                break;
            case OBJECT:
                break;
        }
        ++i;
        ++(*root)->alw_size;
        (*root)->alw_tree   = (struct init **) realloc ( (*root)->alw_tree, ( sizeof (struct init *)*((*root)->alw_size) ) );
    }
    (*root)->alw_tree[(*root)->alw_size-1] = NULL;
}


void pfree ( popt **root ) // We must be free the all pointers :)
{
    unsigned int i = 0;

    while ((*root)->alw_tree[i] != NULL)
    /*
     * In this loop, all elements of alw_tree are traversed until, 
     * as per convention, a NULL is encountered (a NULL is always 
     * present at the end of these elements). Then, based on node_mode, 
     * it determines how deep into the structure it should perform the 
     * free operation.
    */
    {
        switch ( (*root)->alw_tree[i]->node_mode )
        {
            case PFLAG:
                free ((*root)->alw_tree[i]);
                break;
        }

        ++i;
    }

    free ((*root)->avl_tree);
    free ((*root)->alw_tree);
    free (*root);
}
