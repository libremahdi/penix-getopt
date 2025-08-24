#include <stdio.h>
#include "pgetopt.h"


int main ( int argc, char *argv[] )
{
    popt *simple = popt_init ();
    pavl simple_available_flags [] = {
        {"l", flag},{"b", key},EOL
    };

    pset_avl_opts (&simple, simple_available_flags);

    char *error_string;
    if ( (error_string = popt_parse (&simple, argc, argv)) != NULL )
    {
        printf ("Error in %s\n", error_string);
        return -1;
    }
    pfree (&simple);
    return 0;
}


/*

int main ( int argc, char *argv[] )
{
    popt *simple = popt_init ();
    pset_avl_flags (&simple, "ltrh");
    char *array[] = {"output", "o"};
    pset_avl_keys (&simple, array);

    if ( popt_parse (&simple, argc, argv) == -1 )
    {
        error (...);
    }
    int *i=(int *) malloc (sizeof (int));
    char a;
    while ( (a=ploop_getflags (simple, &i)) != EOL ) // EOL is a Macro to set break point
    {
        swtich (a)
        {
            case 'l':
                break;
            case 't':
                break;
        }
    }
    printf ("%d\n", );
    
}

*/