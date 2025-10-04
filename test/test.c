#include "pgetopt.h"
#include <stdio.h>

int main ( int argc, char **argv )
{
    pinit *init = pinit_create ();

    pclass *main = pclass_create ( &init, "main" );
    pinit_set_main_class ( &init, main );
    palw main_allowed_options [] = {
		{ 1, "long_flag" },
		{ 2, "key" },
        EOL
    };
    pclass_set_allowed_options ( &main, main_allowed_options );

    pkey *a=pclass_set_key ( &main, 2, DENY_CUSTOM );
    pkey_set_custom_value (&a, "Value1");

    
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
        { 1 , "krate"     }, // clone master
        { 2 , "remove"    },
        EOL
    };
    pinit_set_allowed_masters ( &init, master_avl );

    usrerr _error = pinit_parser ( &init, argc, argv );
    if ( usererror_parser ( _error, argv ) ) return -1;

    char **_argv;
    switch ( pinit_get_master_id ( init ) )
    {
        case 1:
            // Create Class
            pinit *cr_init = pinit_create ();

            pclass *cr_main = pclass_create ( &cr_init, "main" );
            pinit_set_main_class ( &cr_init, cr_main );
            palw main_allowed_options [] = {
                { 1, "long_flag" },
                EOL
            };
            pclass_set_allowed_options ( &cr_main, main_allowed_options );

            palw cr_master_avl [] = {
                { 1 , "file"    },
                EOL
            };
            pinit_set_allowed_masters ( &cr_init, cr_master_avl );

            char **_argv = pinit_get_master_argv (init);
            int _argc = pinit_get_master_argc (init);

            usrerr cr_error = pinit_parser ( &cr_init, _argc, _argv );
            if ( usererror_parser ( cr_error, _argv ) ) return -1;

            char **cr_argv;
            switch ( pinit_get_master_id ( cr_init ) )
            {
                case 1:
                    printf ("Create File\n");
                    break;
            }

            int i=0, opt_id;
            while ( ( opt_id = pclass_loop_get_opt_id ( cr_main, i ) ) != -1 )
            {
                switch ( opt_id )
                {
                    case (1):
                        printf ("Create: long_flag\n\n");
                        break;
                }
                ++i;
            }

            pclass_free ( &cr_main );
            pinit_free ( &cr_init );
            break;
        case 2:
            printf ("Remove\n");
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