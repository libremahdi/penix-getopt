#ifndef POPT_STRING
#define POPT_STRING

#include "pgetopt.h"



static int pget_flags_list ( char ***flags, int argc, char *argv[] )
{
    unsigned long int lastpoint = 0;

    for ( int i = 1 ; i<argc ; ++i )
    {
        if ( argv[i][0] == '-' && argv[i][1] != '-' )
        {
            for ( int j = 1 ; j <=strlen (argv[i])-1 ; ++j )
            {
                (*flags) = (char **) realloc ((*flags), (sizeof (char*)*(lastpoint+1)));
                (*flags)[lastpoint] = (char *) malloc (sizeof (char)*2);
                (*flags)[lastpoint][0] = argv[i][j];
                (*flags)[lastpoint][1] = '\0';
                ++lastpoint;
            }
        }
    }
    return lastpoint;
}


static int pget_keys_list ( char ***keys, char ***values, int argc, char *argv[] )
/* RETURN VALUE MANUAL
 * If the return value of the function pget_flags_list is a negative number, an error has occurred,
 * and the absolute value of the returned number indicates the index of the problem.
*/
{
    unsigned long int lastpoint = 0;

    for ( int i = 1 ; i<argc ; ++i )
    {
        if (argv[i][0] == '-' && argv[i][1] == '-' && argv [i+1] == NULL )
            return -i; // If a key has no value, this command will be executed.
    }

    for ( int i = 1 ; i<argc ; ++i )
    {
        if ( argv[i][0] == '-' && argv[i][1] == '-' )
        {
            (*keys) = (char **) realloc ((*keys), (sizeof (char*)*(lastpoint+1)));
            (*keys)[lastpoint] = (char *) malloc (sizeof (char)*(strlen (argv[i])));
            strcpy ((*keys)[lastpoint], argv[i]);
    
            (*values) = (char **) realloc ((*values), (sizeof (char*)*(lastpoint+1)));
            (*values)[lastpoint] = (char *) malloc (sizeof (char)*(strlen (argv[i+1])));
            strcpy ((*values)[lastpoint], argv[i+1]);
    
            ++lastpoint;
    
        }
    }
    // printf ("key = %d\n", lastpoint);
    return lastpoint;
}

static bool is_flag_available ( popt root, char *flags )
{
    for ( int i = 0 ; i<root.avl_flags_num ; ++i)
    {
        if ( strcmp (root.avl_flags[i] ,flags) == 0 )
            return true;
    }
    return false;
}

static bool is_key_available ( popt root, char *keys )
{
    for ( int i = 0 ; i<root.avl_keys_num ; ++i)
    {
        if ( strcmp (root.avl_keys[i] ,keys) == 0 )
            return true;    
    }
    // return false;
}

#endif