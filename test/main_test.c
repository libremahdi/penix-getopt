#include "pgetopt.h"
#include <stdio.h>

int main ( int argc, char **argv )
{
    pinit *init = pinit_create ();

    pclass *main = pclass_create ( &init, "main" );

    palw main_allowed_options [] = {
        { 0 , "flag"    },
        { 1 , "Hi"      },
        { 0 , "f"       },
        EOL
    };
    pclass_set_allowed_options ( &main, main_allowed_options );
    printf ("%s\n", main->alw_tree[0]->names[0]);

    pclass_free ( &main );
    pinit_free ( &init );
}