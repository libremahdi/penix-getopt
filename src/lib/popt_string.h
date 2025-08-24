int pget_flags_list ( char ***flags, int argc, char *argv[] )
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