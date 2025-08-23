#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lib/popt_string.h"
#include "pgetopt.h"

popt *popt_init (void)
{
    popt *root = (popt *) malloc (sizeof (popt));
    root->tree = (struct init *) malloc (sizeof (struct init *));
    root->tree = NULL;
    return root;
}

int popt_parse ( popt *root, int argc, char *argv[] )
{
    char **flags;
    int lastpoint= pget_flags_list ( &flags, argc, argv );

    
    /* We must be free the all pointers :)
    */
    for ( int i = 0 ; i < lastpoint ; ++i )
        free (flags[i]);
    free (flags);
}