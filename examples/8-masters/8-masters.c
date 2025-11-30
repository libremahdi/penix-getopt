#include <pgetopt-4.3/pgetopt.h>

#include <stdio.h> // just for printf :)

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
        { 2 , "remove"    },
        { 2,  "rm"        }, // clone master
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
            printf ("Create Master\n");
            break;
        case 2:
            printf ("Remove Master\n");
            break;
    }

    {
        int opt_id, i=0;
        
        while ( ( opt_id = pclass_loop_get_opt_id ( class, i ) ) != -1 )
        {
            switch ( opt_id )
            {
                case (1):
                    printf ("Help Page\n");
                    break;
                case (2):
                    for ( int vi=0 ; vi < pclass_get_key_size ( class, 2 ) ; ++vi )
                    {
                        printf ( "Output = %s\n", pclass_key_loop_get_value ( class, 2, vi ) );
                    }
                    break;
            }
            ++i;
        }
    }
    
    pclass_free (class);
    pinit_free (init);
}

/* Example Export :
 * If you provide no arguments to the software, you should see no output.

 $ ./example -o 1 -h create "This part is not processed."
 Create Master
 Output = 1
 Help Page

 $ ./example rm "This part is not processed."
 Remove Master

 $ ./example remove "This part is not processed."
 Remove Master

*/