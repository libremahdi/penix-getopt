#include "pgetopt.h"
#include <stdio.h>

int main ( int argc, char **argv )
{
    pinit *init = pinit_create ();

    pclass *main = pclass_create ( &init, "main" );
    pinit_set_main_class ( &init, main );
    palw main_allowed_options [] = {
        { 100 , "m"    },
        { 1 ,   "Hi"      },
        { 101 , "f"       },
        EOL
    };
    pclass_set_allowed_options ( &main, main_allowed_options );

    pinit_parser ( &init, argc, argv );

    pclass_free ( &main );
    pinit_free ( &init );
}