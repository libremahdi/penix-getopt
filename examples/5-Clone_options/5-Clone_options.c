#include <pgetopt-4.3/pgetopt.h>

#include <stdio.h> // just for printf :)

int main ( int argc, char **argv )
{
    pinit *init = pinit_create ();
    
    pclass *class = pclass_create ( init, "main" );
    
    pinit_set_main_class ( init, class );

    palw main_allowed_options [] = {
        { 1, "long_flag" },
        { 1, "f" }, // You can assign a single opt_id to multiple different options. In that case, those multiple options will function identically.
        { 2, "long_key" },
        { 2, "k" }, // Rationale: This is for flags and keys that have different names but the same functionality, such as: ( -h, --help ) ( -v, --version )
        EOL
    };

    pclass_set_allowed_options ( class, main_allowed_options );

    pclass_set_key ( class, 2, NONE ); 

    pinit_parser ( init, argc, argv );

    {
        int opt_id, i=0;
        
        while ( ( opt_id = pclass_loop_get_opt_id ( class, i ) ) != -1 ) 
        {
            switch ( opt_id )
            {
                case (1):
                    printf ("this is long_flag OR f\n");
                    break;

                case (2):
                    for ( int vi=0 ; vi < pclass_get_key_size ( class, 2 ) ; ++vi )
                    {
                        printf ( "long_key OR k = %s\n", pclass_key_loop_get_value ( class, 2, vi ) );
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

 $ ./example -f
 this is long_flag OR f

 $ ./example --long_flag
 this is long_flag OR f

 $ ./example --long_key 1 -k 2
 long_key OR k = 1
 long_key OR k = 2

 * The current example does not perform any error handling, so no user errors are issued.
*/