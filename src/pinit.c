#include "pgetopt.h"
#include <stdio.h>

pinit* pinit_create ()
{
    pinit *init         = (pinit *) malloc (sizeof (pinit));
    init->classes_size  = 0;

    init->classes       = (struct object **) malloc ( ( sizeof (struct object *) ) );
    init->classes[0]    = NULL; // this is the main class
    return init;
}

void pinit_free ( pinit **init )
{
    free ( (*init)->classes );
    free ( (*init) );
}