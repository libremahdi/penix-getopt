#include <stdio.h>
#include "pgetopt.h"


int main ( int argc, char *argv[] )
{
    popt *simple = popt_init ();
    pclass_create (&simple, "user");
    pfree (&simple);
    
    return 0;
}

