#include <stdio.h>
#include "pgetopt.h"


int main ( int argc, char *argv[] )
{
    popt *simple = popt_init ();
    pavl simple_available_flags [] = {
        {"l", flag},
        {"t", flag},
        {"r", flag},
        {"h", flag},
        EOL
    };

    pset_avl_opts (&simple, simple_available_flags);

    char *error_string;
    if ( (error_string = popt_parse (&simple, argc, argv)) != NULL )
    {
        printf ("Error in %s\n", error_string);
        return -1;
    }

    int i=0; char ch;
    while ( (ch=ploop_get_flags (simple, i)) != EOO )
    {
        switch (ch)
        {
            case 'l':
                printf ("l is a flag!\n");
                break;
            case 't':
                printf ("t is a flag!\n");
                break;
            case 'r':
                printf ("r is a flag!\n");
                break;
            case 'h':
                printf ("h is a flag!\n");
                break;

        }
        ++i;
    }
    pfree (&simple);
    return 0;
}

