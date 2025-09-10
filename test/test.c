#include "pgetopt.h"
#include <stdio.h>

int main ( int argc, char *argv[] )
{
    pinit *init = pinit_create ();
    pclass *main = pclass_create (&init, "main");
    pclass *user = pclass_create (&init, "user");

    pinit_set_main_class (&init, main);
    
    palw main_allowed_options [] = {
        {"l", FLAG, 100},
        {"output", FLAG, 101},
        EOL
    };

    palw user_allowed_options [] = {
        {"m", FLAG, 100},
        {"input", FLAG, 101},
        EOL
    };



    pclass_set_allowed_options ( &main, main_allowed_options );
    pclass_set_allowed_options ( &user, user_allowed_options );

    int err_index;
    if ( (err_index = pinit_parse (&init, argc, argv)) != 0 )
    {
        printf ("Error in %s\n", argv[err_index]);
        goto err_ret;
    }

    int opt_id, i = 0;
    while ( ( opt_id = pclass_loop_get ( main, i ) ) != -1 )
    {
        switch ( opt_id )
        {
            case (100):
                printf ("FLAG: l\n");
                break;
            case (101):
                printf ("FLAG: output\n");
                break;
        }
        ++i;
    }


err_ret:
    pclass_free (&user);
    pclass_free (&main);
    pinit_free (&init);
    return 0;
}

