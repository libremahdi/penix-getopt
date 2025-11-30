#include <pgetopt-4.2/pgetopt.h>

#include <stdio.h> // just for printf :)



int _create_func ( int, char ** );

int main ( int argc, char **argv )
{
    pinit *init = pinit_create ();
    pclass *class = pclass_create ( init, "main" );
    
    pinit_set_main_class ( init, class );

    palw main_allowed_options [] = {
        { 1, "h" },
        { 1, "help" },
        { 2, "o" },
        { 2, "output" },
        EOL
    };    

    pclass_set_allowed_options ( class, main_allowed_options );
    
    pclass_set_key ( class, 2, NONE ); 

    palw master_avl [] = 
    /* We also use PALW to determine the allowed masters. The masters, just like other options, contain an opt_id. 
     * Masters do not differ from other options in terms of their clone option capability; by setting the same opt_id for two or more options, 
       you can achieve the clone option capability in masters.
    */ {
    //  { opt_id, opt_name },
        { 1 , "create"    },
        EOL
    };
    pinit_set_allowed_masters ( init, master_avl ); // This function updates the PALW structure with master data.

    usrerr _error = pinit_parser ( init, argc, argv );
    
    if ( usererror_parser ( _error, argv ) ) return -1;

    switch ( pinit_get_master_id ( init ) ) // This function returns the opt_id of the single, first master that the user used. There is no need for a loop because no processing is performed on the masters.
    /* Because `Pgetopt` always processes a single master of the user's data and returns all the subsequent data, a check is always performed in 
       the code's flow. That is, there is no need for a loop.
    */
    {
        case 1: // The number 1 is merely a simple identifier of option! (opt_id). for master
            if ( _create_func ( pinit_get_master_argc (init), pinit_get_master_argv (init) ) == -1 )
                return -1;
            break;
    }

    {
        int opt_id, i=0;
        
        while ( ( opt_id = pclass_loop_get_opt_id ( class, i ) ) != -1 ) {
            switch ( opt_id )
            {
                case (1): // The number 1 is merely a simple identifier of option! (opt_id).
                    printf ("Help Page\n");
                    break;
                case (2):
                    for ( int vi=0 ; vi < pclass_get_key_size ( class, 2 ) ; ++vi ) // This function returns the count of a key's values.
                    {
                        printf ( "Output = %s\n", pclass_key_loop_get_value ( class, 2, vi ) ); // This function iterates over the values of a key.
                        /* Its first parameter is the class in which the key opt_id resides.
                         * The second parameter is the option ID that has been converted into the key (or keys).
                         * The third parameter is an index for the iteration (or traversal).
                        */
                    }
                    break;
            }
            ++i;
        }
    }
    
    pclass_free (class);
    pinit_free (init);
}

int _create_func ( int _argc, char **_argv )
{
    pinit *cr_init = pinit_create ();

    pclass *cr_main = pclass_create ( cr_init, "main" );
    pinit_set_main_class ( cr_init, cr_main );
    palw main_allowed_options [] = {
        { 1, "f" },
        EOL
    };
    pclass_set_allowed_options ( cr_main, main_allowed_options );

    palw cr_master_avl [] = {
        { 1 , "file"    },
        EOL
    };
    pinit_set_allowed_masters ( cr_init, cr_master_avl );

    usrerr cr_error = pinit_parser ( cr_init, _argc, _argv );
    if ( usererror_parser ( cr_error, _argv ) ) return -1;

    switch ( pinit_get_master_id ( cr_init ) )
    {
        case 1:
            printf ("Create File\n");
            break;
    }

    int i=0, opt_id;
    while ( ( opt_id = pclass_loop_get_opt_id ( cr_main, i ) ) != -1 )
    {
        switch ( opt_id )
        {
            case (1):
                printf ("Create: this is 'f'\n");
                break;
        }
        ++i;
    }

    pclass_free ( cr_main );
    pinit_free ( cr_init );
}


/* Example Export :
 * If you provide no arguments to the software, you should see no output.

 $ ./example -h -o 1 create -f file
 Create File
 Create: this is 'f'
 Help Page
 Output = 1
*/