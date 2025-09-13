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
        {"output"   , 101},
        EOL
    };
    pclass_set_allowed_options ( &main_class, main_allowed_options );
    
    // key-value segment
    pkey key1 = pclass_set_key ( &main_class, 101, ALW_CUSTOM);
    pkey_custom_set_value ( &key1, "Hello" );
    pkey_custom_set_value ( &key1, "Hi" );
    // end segment

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
                // printf (">%d\n", pclass_get_key_size (main_class, 101));
                printf ("main FLAG: output\n");
                break;
        }
        ++i;
    }


err_ret:
    pclass_free (&main_class);
    pinit_free (&init);
    return 0;
}

