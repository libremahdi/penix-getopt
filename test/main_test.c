#include "pgetopt.h"
#include <stdio.h>

int main ( int argc, char **argv )
{
    pinit *init = pinit_create ();

    pclass *main = pclass_create ( &init, "main" );
    pinit_set_main_class ( &init, main );
    palw main_allowed_options [] = {
        { 100 , "m"    },
        { 101 ,   "Hi"      },
        { 101 , "f"       },
        EOL
    };
    pclass_set_allowed_options ( &main, main_allowed_options );

    pkey *Hi_key = pclass_set_key (&main, 100, NONE);
    // pkey_set_custom_value ( &Hi_key, "First" );
    // pkey_set_custom_value ( &Hi_key, "Last" );
    // printf ("%s\n", pkey_key_loop_get_value ( Hi_key, 0 )) ;

    
    pclass *user = pclass_create ( &init, "user" );
    palw user_allowed_options [] = {
        { 1 , "m"    },
        { 2 ,   "Hi"      },
        { 2 , "f"       },
        EOL
    };
    pclass_set_allowed_options ( &user, user_allowed_options );
    pkey *Hi_key1 = pclass_set_key (&user, 1, DENY_CUSTOM);
    pkey_set_custom_value ( &Hi_key1, "First" );



    pinit_parser ( &init, argc, argv );


    int opt_id, i;

    i=0;
    while ( ( opt_id = pclass_loop_get_id ( main, i ) ) != -1 )
    {
        switch ( opt_id )
        {
            case (100):
                for ( int i = 0 ; i < pclass_get_key_size (main, 100) ; ++i )
                {
                    printf ("Class=main ; key ; Value = %s\n", pclass_key_loop_get_value (main, 100, i));
                }
                break;
            case (101):
                printf ("Class=main : flag=Hi or f\n");
                break;

        }
        ++i;
    }

    i=0;
    while ( ( opt_id = pclass_loop_get_id ( user, i ) ) != -1 )
    {
        switch ( opt_id )
        {
            case (1):
                for ( int i = 0 ; i < pclass_get_key_size (user, 1) ; ++i )
                {
                    printf ("Class=user ; key ; Value = %s\n", pclass_key_loop_get_value (user, 1, i));
                }
                break;
            case (2):
                printf ("Class=user : flag=Hi or f\n");
                break;

        }
        ++i;
    }
    pclass_free ( &user );
    pclass_free ( &main );
    pinit_free ( &init );
}