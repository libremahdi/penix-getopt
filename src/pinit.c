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
            ( (opt_id = get_id ( (*init)->classes[0], argv[i]+1 )) == -1 ) && ( printf ("Error %d\n", __LINE__), abort (), 0 );

            switch ( get_key_type ( (*init)->classes[0], opt_id ) )
            {
                case VOID:
                    if ( is_avl_tree_repetitive_id ( (*init)->classes[0], opt_id ) == -1 ) // -1 means no
                        _phead_flag ( init, 0, opt_id);
                    break;
                default:
                    if ( is_avl_tree_repetitive_id ( (*init)->classes[0], opt_id ) == -1 ) // -1 means no
                    {
                        ( _phead_key ( init, 0, opt_id, argv[i+1] ) == -1 ) && ( printf ("Error %d\n", __LINE__), abort (), 0 );
                        ++i;
                        continue;
                    }
                    ( _phead_repetitive_key ( init, 0, opt_id, argv[i+1] ) == -1 ) && ( printf ("Error %d\n", __LINE__), abort (), 0 );
                    ++i;
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
                
                ( (opt_id = get_id ( (*init)->classes[0], char2strv )) == -1 ) && ( printf ("Error %d\n", __LINE__), free (char2strv), abort (), 0 );
                
                if ( is_avl_tree_repetitive_id ( (*init)->classes[0], opt_id ) == -1 ) // -1 means no
                    _phead_flag ( init, 0, opt_id);

            }

        }
        else if ( argv[i][0] == '-' && argv[i][1] == '-' ) // long options
        {
            ( (opt_id = get_id ( (*init)->classes[0], argv[i] + 2 )) == -1 ) && ( printf ("Error %d\n", __LINE__), abort (), 0 );

            switch ( get_key_type ( (*init)->classes[0], opt_id ) )
            {
                case VOID:
                    if ( is_avl_tree_repetitive_id ( (*init)->classes[0], opt_id ) == -1 ) // -1 means no
                        _phead_flag ( init, 0, opt_id);
                    break;
                default:
                    if ( is_avl_tree_repetitive_id ( (*init)->classes[0], opt_id ) == -1 ) // -1 means no
                    {
                        ( _phead_key ( init, 0, opt_id, argv[i+1] ) == -1 ) && ( printf ("Error %d\n", __LINE__), abort (), 0 );
                        ++i;
                        continue;
                    }
                    ( _phead_repetitive_key ( init, 0, opt_id, argv[i+1] ) == -1 ) && ( printf ("Error %d\n", __LINE__), abort (), 0 );
                    ++i;
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


            ( (opt_id = get_id ( (*init)->classes[class_index], class_value )) == -1 ) && ( printf ("Error %d\n", __LINE__) , abort (), 0 );
            free (class_value);

            switch ( get_key_type ( (*init)->classes[class_index], opt_id ) )
            {
                case VOID:
                    if ( is_avl_tree_repetitive_id ( (*init)->classes[class_index], opt_id ) == -1 ) // -1 means no
                        _phead_flag ( init, class_index, opt_id);
                    break;
                default:
                    if ( is_avl_tree_repetitive_id ( (*init)->classes[class_index], opt_id ) == -1 ) // -1 means no
                    {
                        ( _phead_key ( init, class_index, opt_id, argv[i+1] ) == -1 ) && ( printf ("Error %d\n", __LINE__), abort (), 0 );
                        ++i;
                        continue;
                    }
                    ( _phead_repetitive_key ( init, class_index, opt_id, argv[i+1] ) == -1 ) && ( printf ("Error %d\n", __LINE__), abort (), 0 );
                    ++i;
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