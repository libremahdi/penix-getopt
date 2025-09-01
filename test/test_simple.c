#include <stdio.h>
#include "pgetopt.h"


int main ( int argc, char *argv[] )
{
    popt *simple = popt_init ();

    /*
    In this form and through this structure, 
    you define the functionality of each option—specifying whether 
    it is a `FLAG`, a `KEY`, or an `OBJECT`.
    */
    palw simple_allowed_options [] = {
        {"l", FLAG}, // you can set a lower character as flag
        {"T", FLAG}, // you can set an upper character as flag
        EOL // End Of List
    };
    pset_alw_opts ( &simple, simple_allowed_options );

    pfree (&simple);
    return 0;
}

