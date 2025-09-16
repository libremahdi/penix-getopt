#include "pgetopt.h"
#include <stdio.h>

int main ( int argc, char **argv )
{
    pinit *init = pinit_create ();

    pinit_free ( &init );
}