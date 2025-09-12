#include "pgetopt.h"
#include <stdio.h>


int main ( int argc, char *argv[] )
{
    pinit *init = pinit_create ();

    // main's class segment
    pclass *main_class = pclass_create (&init, "main");
    pinit_set_main_class (&init, main_class);
    palw main_allowed_options [] = {
        {"l", FLAG, 100},
        {"output", FLAG, 101},
        EOL
    };
    pclass_set_allowed_options ( &main_class, main_allowed_options );

    // user's class segment
    pclass *user = pclass_create (&init, "user");
    palw user_allowed_options [] = {
        {"m", FLAG, 100},
        {"input", FLAG, 101},
        EOL
    };
    pclass_set_allowed_options ( &user, user_allowed_options );

    
    // parsing the options from arguments and managing errors
    int err_index = pinit_parse (&init, argc, argv);
    if ( err_index != 0 )
    {
        printf ("Error in %s\n", argv[err_index]);
        goto err_ret;
    }

    // get options loop segment
    int opt_id, i;

    i = 0;
    while ( ( opt_id = pclass_loop_get ( main_class, i ) ) != -1 )
    {
        switch ( opt_id )
        {
            case (100):
                printf ("main FLAG: l\n");
                break;
            case (101):
                printf ("main FLAG: output\n");
                break;
        }
        ++i;
    }

    i=0;
    while ( ( opt_id = pclass_loop_get ( user, i ) ) != -1 )
    {
        switch ( opt_id )
        {
            case (100):
                printf ("user FLAG: m\n");
                break;
            case (101):
                printf ("user FLAG: input\n");
                break;
        }
        ++i;
    }
    // end of segment

err_ret:
    pclass_free (&user);
    pclass_free (&main_class);
    pinit_free (&init);
    return 0;
}

