#include "pgetopt.h"


int main ( int argc, char *argv[] )
{
    popt *init = popt_init ();
    pclass *main = pclass_create (&init, "main");
    pclass_free (&main);


    pinit_free (&init);
    return 0;
}

