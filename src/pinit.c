#include <stdio.h>
#include <string.h>

#include "pgetopt.h"
#include "lib/popt_init.h"
#include "lib/popt_class.h"

pinit* pinit_create ()
{   pinit *init         = (pinit *) malloc (sizeof (pinit));
    init->classes_size  = 1;

    init->classes       = (struct class **) malloc ( ( sizeof (struct class *) ) );
    init->classes[0]    = NULL; // this is the main class

    init->alw_masters_size = 0;
    init->avl_master    = NULL;
    init->alw_masters   = NULL;

    return init;
}



pgoerr pinit_parser ( pinit **init, int argc, char **argv )

{
    char *char2strv = NULL;
    pgoerr return_err;
    int opt_id;

    union _INDEX { int class_id; int master_id; } glob_index;

    char *class_name = NULL;
    char *class_value = NULL;

    for ( int i = 1 ; i < argc ; ++i )
    {
        if ( (argv[i][0] == '-') && (argv[i][1] != '-') && (strlen (argv[i]) == 2) ) // it's either a single short flag or a key
        {
            ( (opt_id = get_opt_id ( (*init)->classes[0], argv[i]+1 )) == -1 ) && ( printf ("Error %d\n", __LINE__), abort (), 0 );

            switch ( get_key_type ( (*init)->classes[0], opt_id ) )
            {
                case VOID:
                    if ( is_avl_tree_repetitive_id ( (*init)->classes[0], opt_id ) == -1 ) // -1 means no
                        _phead_flag ( init, 0, opt_id);
                    break;
                default:
                    if ( (i+1 >= argc) || (!IsValueReallyAValue (argv[i+1])) )  ( printf ("Error %d\n", __LINE__), abort (), 0 );

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
                
                ( (opt_id = get_opt_id ( (*init)->classes[0], char2strv )) == -1 ) && ( printf ("Error %d\n", __LINE__), free (char2strv), abort (), 0 );
                ( (*get_alw_point ( (*init)->classes[0], opt_id ))->key_type != VOID ) && ( printf ("Error %d\n", __LINE__), free (char2strv), abort (), 0 ); // if M is a key and F is a flag, they cannot be written in compressed (-MF or -FM)
                if ( is_avl_tree_repetitive_id ( (*init)->classes[0], opt_id ) == -1 ) // -1 means no
                    _phead_flag ( init, 0, opt_id);

            }

        }
        else if ( argv[i][0] == '-' && argv[i][1] == '-' ) // long options
        {
            ( (opt_id = get_opt_id ( (*init)->classes[0], argv[i] + 2 )) == -1 ) && ( printf ("Error %d\n", __LINE__), abort (), 0 );

            switch ( get_key_type ( (*init)->classes[0], opt_id ) )
            {
                case VOID:
                    if ( is_avl_tree_repetitive_id ( (*init)->classes[0], opt_id ) == -1 ) // -1 means no
                        _phead_flag ( init, 0, opt_id);
                    break;
                default:
                    if ( (i+1 >= argc) || (!IsValueReallyAValue (argv[i+1])) )  abort();

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

            if ( (glob_index.class_id = get_class_index ((*init), class_name)) == -1 ) 
            {
                free (class_name);
                free (class_value);
                free (char2strv);
                printf ("Error %d\n", __LINE__); 
                abort ();
            }
            free (class_name);
            free (char2strv);


            ( (opt_id = get_opt_id ( (*init)->classes[glob_index.class_id], class_value )) == -1 ) && ( printf ("Error %d\n", __LINE__) , abort (), 0 );
            free (class_value);

            switch ( get_key_type ( (*init)->classes[glob_index.class_id], opt_id ) )
            {
                case VOID:
                    if ( is_avl_tree_repetitive_id ( (*init)->classes[glob_index.class_id], opt_id ) == -1 ) // -1 means no
                        _phead_flag ( init, glob_index.class_id, opt_id);
                    break;
                default:
                    if ( (i+1 >= argc) || (!IsValueReallyAValue (argv[i+1])) )  abort();

                    if ( is_avl_tree_repetitive_id ( (*init)->classes[glob_index.class_id], opt_id ) == -1 ) // -1 means no
                    {
                        ( _phead_key ( init, glob_index.class_id, opt_id, argv[i+1] ) == -1 ) && ( printf ("Error %d\n", __LINE__), abort (), 0 );
                        ++i;
                        continue;
                    }
                    ( _phead_repetitive_key ( init, glob_index.class_id, opt_id, argv[i+1] ) == -1 ) && ( printf ("Error %d\n", __LINE__), abort (), 0 );
                    ++i;
                    break;
            }
        }
        else {
            ( (glob_index.master_id = get_master_id ( (*init), argv[i] )) == -1 ) && ( printf ("Error %d\n", __LINE__), abort (), 0 );
            (*init)->avl_master = ( struct master_avl * ) malloc ( sizeof (struct master_avl) );
            (*init)->avl_master -> name = argv[i];
            (*init)->avl_master -> master_id = glob_index.master_id;
            (*init)->avl_master -> options_size = argc - i;
            (*init)->avl_master -> options = get_master_options ( argc, argv, i );
            break;
        }
        
    }
    // return 0;

}

void pinit_set_main_class ( pinit **init, pclass *class )
{   (*init)->classes[0] = class;
}

void pinit_set_allowed_masters ( pinit **init, palw *allowed_names )
{
    unsigned long int i = 0;
    while ( allowed_names[i].option_name != NULL )
    {
        (*init)->alw_masters = ( struct master_alw ** ) realloc ( (*init)->alw_masters , ( sizeof ( struct master_alw * ) * ((*init)->alw_masters_size+1) ) );
        (*init)->alw_masters [ (*init)->alw_masters_size ] = ( struct master_alw * ) malloc ( sizeof ( struct master_alw ) );
        (*init)->alw_masters [ (*init)->alw_masters_size ] -> name = allowed_names[i].option_name;
        (*init)->alw_masters [ (*init)->alw_masters_size ] -> master_id = allowed_names[i].option_id;
        ++i;
        ++(*init)->alw_masters_size;
    }
}



int pinit_get_master_argc ( pinit  *init )
{
    return init->avl_master->options_size;
}

char **pinit_get_master_argv ( pinit  *init )
{
    return init->avl_master->options;
}


char *pinit_get_master_name ( pinit  *init )
{
    if ( init -> avl_master == NULL)    
    {
        printf ("Error %d\n", __LINE__); 
        abort ();
    }
    return init->avl_master->name;
}

int pinit_get_master_id ( pinit  *init )
{
    if ( init -> avl_master == NULL)    
    return -1;
    return init->avl_master->master_id;
}


void pinit_free ( pinit **init )
{   
    free ( (*init)->classes );

    for ( int i = 0 ; i < (*init)->alw_masters_size ; ++i )
    {
        free ( (*init)->alw_masters[i] );
    }

    free ( (*init)->alw_masters );

    if ((*init)->avl_master != NULL) free ( (*init)->avl_master->options );
    free ( (*init)->avl_master );
    free ( (*init) );
}
