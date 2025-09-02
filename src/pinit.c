#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pgetopt.h"


popt *popt_init (void)
{
    popt *init          = (popt *) malloc (sizeof (popt));
    init->class_size    = 0;
    init->classes       = NULL;
    return init;
}

void pinit_allowed_opts ( pclass **class, palw *alw_opts )
{
    unsigned long int i = 0;

    while (alw_opts[i].option_name != NULL)
    {
        switch (alw_opts[i].option_mode)
        {
            case FLAG:
                printf ("%s\n", alw_opts[i].option_name);
                (*class)->alw_tree = (struct branch **) realloc ( (*class)->alw_tree, ( sizeof (struct branch *) * ((*class)->alw_size + 1) ) );
                (*class)->alw_tree[(*class)->alw_size] = (struct branch *) malloc ( sizeof (sizeof (struct branch *)));
                (*class)->alw_tree[(*class)->alw_size]->name = alw_opts[i].option_name;
                (*class)->alw_tree[(*class)->alw_size]->node_mode = FLAG;
                (*class)->alw_tree[(*class)->alw_size]->values_size = 0;
                (*class)->alw_tree[(*class)->alw_size]->values = NULL;

        }
        ++i;
    }
}

void pinit_free ( popt **init )
{
    free ((*init)->classes);
    free (*init);
}



