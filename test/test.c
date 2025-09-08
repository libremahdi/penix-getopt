#include "pgetopt.h"
#include <stdio.h>

int main ( int argc, char *argv[] )
{
    pinit *init = pinit_create ();
    pclass *main = pclass_create (&init, "main");

    pinit_set_main_class (&init, main);
    
    palw simple_available_flags [] = {
        {"l", FLAG, 100},
        {"t", FLAG, 101},
        {"r", FLAG, 102},
        {"h", FLAG, 103},
        {"hello", FLAG, 104},
        EOL
    };

    pclass_set_allowed_options ( &main, simple_available_flags );

    int err_index;
    if ( (err_index = pinit_parse (&init, argc, argv)) != 0 )
    {
        printf ("Error in %s\n", argv[err_index]);
        goto err_ret;
    }

    int opt_id, i = 0;
    while ( (opt_id = pclass_loop_get ( main, i )) != -1 )
    {
        switch ( opt_id )
        {
            case (100):
                // printf ("FLAG: l\n");
                break;
            case (101):
                // printf ("FLAG: t\n");
                break;
            case (102):
                // printf ("FLAG: r\n");
                break;
            case (103):
                // printf ("FLAG: h\n");
                break;
            case (104):
                // printf ("FLAG: multi_letter\n");
                break;
        }
        ++i;
    }


err_ret:
    pclass_free (&main);
    pinit_free (&init);
    return 0;
}

