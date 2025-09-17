#include <stdio.h>
#include <string.h>

#include "pgetopt.h"
#include "lib/popt_init.h"
#include "lib/popt_class.h"

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

    unsigned int class_index;    
    char *class_name = NULL;
    char *class_value = NULL;

    for ( int i = 1 ; i < argc ; ++i )
    {
        if ( (argv[i][0] == '-') && (argv[i][1] != '-') && (strlen (argv[i]) == 2) ) // it's either a single short flag or a key
        {
            if ( (opt_id = get_id ( (*init)->classes[0], argv[i]+1 )) == -1 ) 
            { 
                printf ("Error %d\n", __LINE__); 
                abort ();
            }

            switch ( get_key_type ( (*init)->classes[0], opt_id ) )
            {
                case VOID:
                    if ( is_avl_tree_repetitive_id ( (*init)->classes[0], opt_id ) == -1 ) // -1 means no
                    {
                        (*init)->classes[0]->avl_tree = ( struct avl_branch **) realloc ( ((*init)->classes[0]->avl_tree), ( sizeof (struct avl_branch *) * ( (*init)->classes[0]->avl_size + 1 )) );
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size] = ( struct avl_branch * ) malloc ( sizeof ( struct avl_branch ) );
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->opt_id        = opt_id;
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values_size   = 0;
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values        = NULL;
                        ++(*init)->classes[0]->avl_size;
                    }
                    break;
                default:
                    // key
                    break;
            }
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
                    printf ("Error %d\n", __LINE__); 
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
            if ( (opt_id = get_id ( (*init)->classes[0], argv[i] + 2 )) == -1 ) 
            { 
                printf ("Error %d\n", __LINE__); 
                abort ();
            }

            switch ( get_key_type ( (*init)->classes[0], opt_id ) )
            {
                case VOID:
                    if ( is_avl_tree_repetitive_id ( (*init)->classes[0], opt_id ) == -1 ) // -1 means no
                    {
                        (*init)->classes[0]->avl_tree = ( struct avl_branch **) realloc ( ((*init)->classes[0]->avl_tree), ( sizeof (struct avl_branch *) * ( (*init)->classes[0]->avl_size + 1 )) );
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size] = ( struct avl_branch * ) malloc ( sizeof ( struct avl_branch ) );
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->opt_id        = opt_id;
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values_size   = 0;
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values        = NULL;
                        ++(*init)->classes[0]->avl_size;
                    }
                    break;
                default:
                    // key
                    break;
            }
        }
        else if ( argv[i][0] == '@' ) // Must be a class
        {
            char2strv   = strdup (argv[i]+1);
            if ( !is_class_syntax_correct (char2strv) )
            {
                free (char2strv);
                printf ("Error %d\n", __LINE__); 
                abort ();
            }
            class_name  = pstr_get_class_name (char2strv);
            class_value = pstr_get_class_value (char2strv);

            if ( (class_index = get_class_index ((*init), class_name)) == -1 ) 
            {
                free (class_name);
                free (class_value);
                free (char2strv);
                printf ("Error %d\n", __LINE__); 
                abort ();
            }
            free (class_name);
            free (char2strv);

            if ( (opt_id = get_id ( (*init)->classes[class_index], class_value )) == -1 ) 
            { 
                printf ("Error %d\n", __LINE__); 
                abort ();
            }
            free (class_value);

            switch ( get_key_type ( (*init)->classes[class_index], opt_id ) )
            {
                case VOID:
                    if ( is_avl_tree_repetitive_id ( (*init)->classes[class_index], opt_id ) == -1 ) // -1 means no
                    {
                        (*init)->classes[class_index]->avl_tree = ( struct avl_branch **) realloc ( ((*init)->classes[class_index]->avl_tree), ( sizeof (struct avl_branch *) * ( (*init)->classes[class_index]->avl_size + 1 )) );
                        (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size] = ( struct avl_branch * ) malloc ( sizeof ( struct avl_branch ) );
                        (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size]->opt_id        = opt_id;
                        (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size]->values_size   = 0;
                        (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size]->values        = NULL;
                        ++(*init)->classes[class_index]->avl_size;
                    }
                    break;
                default:
                    // key
                    break;
            }
        }
        else {
            printf ("This is Master key : %s\n", argv[i]);
            // check that the Master key is correct
            // then, send all the options to the end of the arguments in order
            // to implement a feature like this : $ git commit -m "Hello"
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