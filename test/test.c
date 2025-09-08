#include "pgetopt.h"
#include <stdio.h>

int main ( int argc, char *argv[] )
{
    pinit *init = pinit_create ();
    pclass *main = pclass_create (&init, "main");

    pinit_set_main_class (&init, main);
    
    palw simple_available_flags [] = {
        {"H", FLAG, 100},
        {"Hello", FLAG, 101},
        EOL
    };

    pclass_set_allowed_options ( &main, simple_available_flags );

    int err_index;
    if ( (err_index = pinit_parse (&init, argc, argv)) != 0 )
    {
        printf ("Error in %s\n", argv[err_index]);
        goto err_ret;
    }

err_ret:
    pclass_free (&main);
    pinit_free (&init);
    return 0;
}

