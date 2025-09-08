#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#include "pgetopt.h"
#include "lib/popt_tree.h"

pinit* pinit_create ( int INIT_MODE )
{
    pinit *init          = (pinit *) malloc (sizeof (pinit));
    init->classes_index = 1; // first index is for main class

    init->classes = (struct object **) malloc ( ( sizeof (struct object *) ) );
    init->classes[0] = NULL; // this is the main class
    return init;
}

int pinit_parse ( pinit **init, int argc, char **argv )
{
    char *char2strv = NULL;
    
    for ( int i = 1 ; i < argc ; ++i )
    {
        if ( argv[i][0] == '-' && argv[i][1] != '-' )
        {
            for ( int j = 1 ; j <=strlen (argv[i])-1 ; ++j )
            {
                char2strv = (char *) realloc (char2strv, sizeof (char)*2);
                
                char2strv[0]=argv[i][j];
                char2strv[1]='\0';
                // printf ("%s\n", char2strv);
                switch ( is_alw ((*init)->classes[0], char2strv) )
                {
                    case FLAG:
                        if ( is_repetitive_flag ( (*init)->classes[0], char2strv ) == true )   continue;
                        (*init)->classes[0]->avl_tree = ( struct branch ** ) realloc ( (*init)->classes[0]->avl_tree , (sizeof (struct branch *)*((*init)->classes[0]->avl_size+1)) );
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size] = (struct branch *) malloc (sizeof (struct branch)*(strlen (char2strv)+1));
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->name          = char2strv;
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->ID            = what_is_ID ((*init)->classes[0], char2strv);
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values_size   = 0;
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values        = NULL;
                        
                        ++(*init)->classes[0]->avl_size;
                        break;    
                    case -1:
                        free (char2strv);
                        return i;
                }
            }
        }
        else if ( argv[i][0] == '-' && argv[i][1] == '-' )
        {
            char2strv = strdup (argv[i]+2);

            switch ( is_alw ((*init)->classes[0], char2strv) )
            {
                case FLAG:
                    if ( is_repetitive_flag ( (*init)->classes[0], char2strv ) == true )   continue;
                    (*init)->classes[0]->avl_tree = ( struct branch ** ) realloc ( (*init)->classes[0]->avl_tree , (sizeof (struct branch *)*((*init)->classes[0]->avl_size+1)) );
                    (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size] = (struct branch *) malloc (sizeof (struct branch)*(strlen (char2strv)+1));
                    (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->name          = char2strv;
                    (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->ID            = what_is_ID ((*init)->classes[0], char2strv);
                    (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values_size   = 0;
                    (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values        = NULL;

                    ++(*init)->classes[0]->avl_size;
                    break;  
                case -1:
                    free (char2strv);
                    return i;
            }
        }
    }
    free (char2strv);
    return 0; // The function returns 0 when all options are valid and no issues are present.
}

void pinit_set_main_class ( pinit **init, pclass *class )
{
    (*init)->classes[0] = class;
}


void pinit_free ( pinit **init )
{
    free ((*init)->classes);
    free (*init);
}



