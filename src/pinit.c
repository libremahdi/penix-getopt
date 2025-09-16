#include <stdio.h>
#include <string.h>

#include "pgetopt.h"
#include "lib/popt_init.h"

pinit* pinit_create ()
{   pinit *init         = (pinit *) malloc (sizeof (pinit));
    init->classes_size  = 1;

    init->classes       = (struct object **) malloc ( ( sizeof (struct object *) ) );
    init->classes[0]    = NULL; // this is the main class
    return init;
}

pgoerr pinit_parser ( pinit **init, int argc, char **argv )

{
    char *char2strv = NULL;
    pgoerr return_err;
    int opt_id;

    for ( int i = 1 ; i < argc ; ++i )
    {
        if ( (argv[i][0] == '-') && (argv[i][1] != '-') && (strlen (argv[i]) == 2) ) // it's either a single short flag or a key
        {

        }
        else if ( (argv[i][0] == '-') && (argv[i][1] != '-') ) // They must be flag
        {
            for ( int j = 1 ; j <= strlen (argv[i])-1 ; ++j )
            {
                char2strv = ( char * ) malloc ( sizeof (char) * 2 );
                char2strv[0] = argv[i][j]; 
                char2strv[1]='\0';
                
                if ( (opt_id = get_id ( (*init)->classes[0], char2strv )) == -1 ) 
                { 
                    printf ("Error\n"); 
                    free (char2strv);
                    abort ();
                }
                
                if ( is_avl_tree_repetitive_id ( (*init)->classes[0], opt_id ) == -1 ) // -1 means no
                {
                    (*init)->classes[0]->avl_tree = ( struct avl_branch **) realloc ( ((*init)->classes[0]->avl_tree), ( sizeof (struct avl_branch *) * ( (*init)->classes[0]->avl_size + 1 )) );
                    (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size] = ( struct avl_branch * ) malloc ( sizeof ( struct avl_branch ) );
                    (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->opt_id        = opt_id;
                    (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values_size   = 0;
                    (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values        = NULL;
                    ++(*init)->classes[0]->avl_size;
                }

            }

        }
        else if ( argv[i][0] == '-' && argv[i][1] == '-' ) // long options
        {

        }
        else if ( argv[i][0] == '@' ) // Must be a class
        {

        }

    }

}


void pinit_set_main_class ( pinit **init, pclass *class )
{   (*init)->classes[0] = class;
}


void pinit_free ( pinit **init )
{   free ( (*init)->classes );
    free ( (*init) );
}