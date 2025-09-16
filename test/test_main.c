/* The file main_test.c is a general test file for the developer. There is no specific functionality of the library being tested in this file. This file is solely for the developer to test their latest changes.
 * To compile and use this file, enter the following command:

 $ make test_main
 
 * This command creates a binary file with the same name in `~/build`.
*/

#include "pgetopt.h"
#include <stdio.h>


int main ( int argc, char *argv[] )
{
    pinit *init = pinit_create ();


    pclass *main_class = pclass_create (&init, "main");
    pinit_set_main_class (&init, main_class);
    palw main_allowed_options [] = {
        {"long_flag"   , 100},
        {"f"           , 100}, // short flag
        {"l"           , 100}, // short flag 2
        {"long_key"    , 101},
        EOL
    };
    pclass_set_allowed_options ( &main_class, main_allowed_options );

    pkey key = pclass_set_key ( &main_class, 101, NONE);


    pclass *user = pclass_create (&init, "user");
    palw user_alw [] = {
        {"long_flag"    , 1},
        {"f"            , 1},
        {"long_key"     , 2},
        EOL
    };
    pclass_set_allowed_options ( &user, user_alw );

    pkey key1 = pclass_set_key ( &user, 2, NONE);






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
                printf ("Class=main_class : flag\n");
                break;
            case (101):
                for ( int in = 0 ; in < pclass_get_key_size (main_class, 101) ; ++in )
                {
                    printf ("Class=main_class : key : Value = %s\n", pclass_get_value(main_class, 101, in));
                }
                break;

        }
        ++i;
    }
    i=0;
    while ( ( opt_id = pclass_loop_get ( user, i ) ) != -1 )
    {
        switch ( opt_id )
        {
            case (1):
                printf ("Class=user : flag\n");
                break;
            case (2):
                for ( int in = 0 ; in < pclass_get_key_size (user, 2) ; ++in )
                {
                    printf ("Class=user ; key ; Value = %s\n", pclass_get_value(user, 2, in));
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

