#include "pgetopt.h"
#include <stdio.h>

int main ( int argc, char **argv )
{


    // pgoerr return_err;

    // return_err.error=1;
    // return_err.index=1;

    // int a=pgoerror_parser (return_err, argv);
    // printf ("%d\n", a);
    // return 0;

    pinit *init = pinit_create ();

    pclass *main = pclass_create ( &init, "main" );
    pinit_set_main_class ( &init, main );
    palw main_allowed_options [] = {
		{ 1, "long_flag" },
		{ 2, "key" },
        EOL
    };
    pclass_set_allowed_options ( &main, main_allowed_options );

    pclass_set_key ( &main, 2, NONE );

    
    pclass *user = pclass_create ( &init, "user" );
    palw user_allowed_options [] = {
		{ 1, "name" },
		{ 2, "ID" },
        EOL
    };
    pclass_set_allowed_options ( &user, user_allowed_options );
    pclass_set_key (&user, 1, NONE);
    pclass_set_key (&user, 2, NONE);


    palw master_avl [] = {
        { 1 , "create"    },
        { 2 , "remove"    },
        EOL
    };
    pinit_set_allowed_masters ( &init, master_avl );

    pgoerr _error = pinit_parser ( &init, argc, argv );
    if ( pgoerror_parser ( _error, argv ) ) return -1;

    char **_argv;
    switch ( pinit_get_master_id ( init ) )
    {
        case 1:
            printf ("Create Master\n");
            _argv = pinit_get_master_argv(init);
            for ( int i = 0 ; i < pinit_get_master_argc (init) ; ++i )
            {
                printf ("i=%d:%s\n", i, _argv[i]);
            }
            printf ("\n");
            break;
        case 2:
            printf ("Remove Master\n");
            _argv = pinit_get_master_argv(init);
            for ( int i = 0 ; i < pinit_get_master_argc (init) ; ++i )
            {
                printf ("i=%d:%s\n", i, _argv[i]);
            }
            printf ("\n");
            break;
    }

    int opt_id, i;

    i=0;
    while ( ( opt_id = pclass_loop_get_opt_id ( main, i ) ) != -1 )
    {
        switch ( opt_id )
        {
            case (1):
                printf ("long_flag\n");
                break;
            case (2):
                for ( int vi=0 ; vi < pclass_get_key_size ( main, 2 ) ; ++vi )
                {
                    printf ( "key = %s\n", pclass_key_loop_get_value ( main, 2, vi ) );
                }
                break;

        }
        ++i;
    }

    i=0;
    while ( ( opt_id = pclass_loop_get_opt_id ( user, i ) ) != -1 )
    {
        switch ( opt_id )
        {
            case (1):
                for ( int vi=0 ; vi < pclass_get_key_size ( user, 1 ) ; ++vi )
                {
                    printf ( "name = %s\n", pclass_key_loop_get_value ( user, 1, vi ) );
                }
                break;
            case (2):
                for ( int vi=0 ; vi < pclass_get_key_size ( user, 2 ) ; ++vi )
                {
                    printf ( "ID = %s\n", pclass_key_loop_get_value ( user, 2, vi ) );
                }
                break;
        }
        ++i;
    }
    pclass_free ( &user );
    pclass_free ( &main );
    pinit_free ( &init );
}