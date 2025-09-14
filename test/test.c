#include "pgetopt.h"
#include <stdio.h>


int main ( int argc, char *argv[] )
{
    pinit *init = pinit_create ();

    // main's class segment
    pclass *main_class = pclass_create (&init, "main");
    pinit_set_main_class (&init, main_class);
    palw main_allowed_options [] = {
        {"l"        , 100},
        {"o"        , 101},
        EOL
    };
    pclass_set_allowed_options ( &main_class, main_allowed_options );

    pkey key = pclass_set_key ( &main_class, 101, ALW_CUSTOM);
    pkey_custom_set_value ( &key, "Hello" );


    pclass *user = pclass_create (&init, "user");
    palw user_alw [] = {
        {"name"   , 1},
        {"poweroff"  , 2},
        EOL
    };
    pclass_set_allowed_options ( &user, user_alw );

    pkey key1 = pclass_set_key ( &user, 1, ALW_CUSTOM);
    pkey_custom_set_value ( &key1, "Hello" );






    pgoerr err_index = pinit_parse (&init, argc, argv);
    // if ( err_index.error != 0 ) // Manual error Managment. 
    // {
        // printf ("Error in %s\n", argv[err_index.index]); 
        // goto err_ret;
    // }

    if ( pgoerror_parser (err_index, argv) ) goto err_ret; // Automatic error parsing

    int opt_id, i;

    i = 0;

    while ( ( opt_id = pclass_loop_get ( main_class, i ) ) != -1 )
    {
        switch ( opt_id )
        {
            case (100):
                printf ("Class=main_class : flag=l\n");
                break;
            case (101):
                for ( int in = 0 ; in < pclass_get_key_size (main_class, 101) ; ++in )
                {
                    printf ("Class=main_class : key=o : Value = %s\n", pclass_get_value(main_class, 101, in));
                }
                break;
        }
        ++i;
    }
    printf ("\n");
    i=0;
    while ( ( opt_id = pclass_loop_get ( user, i ) ) != -1 )
    {
        switch ( opt_id )
        {
            case (2):
                printf ("Class=user : flag=poweroff\n");
                break;
            case (1):
                for ( int in = 0 ; in < pclass_get_key_size (user, 1) ; ++in )
                {
                    printf ("Class=user ; key=name ; Value = %s\n", pclass_get_value(user, 1, in));
                }
                break;
        }
        ++i;
    }


err_ret:
    pclass_free (&main_class);
    pclass_free (&user);
    pinit_free (&init);
    return 0;
}

