#include <pgetopt-4.3/pgetopt.h>

#include <stdio.h> // just for printf :)

int main ( int argc, char **argv )
{
    pinit *init = pinit_create ();
    
    pclass *class = pclass_create ( init, "main" );
    
    pinit_set_main_class ( init, class );

    palw main_allowed_options [] = {
        { 1, "long_flag" },
        { 2, "f" },
        { 3, "long_key" },
        { 4, "k" },
        EOL
    };    

    pclass_set_allowed_options ( class, main_allowed_options );

    pkey *key;
    
    key = pclass_set_key ( class, 3, ALW_CUSTOM ); // This function designates an option ID as a key.
    /* In pgetopt, if you don't select an option to be a key, it is considered a Flag. If you configure 
       it as a key using the pclass_set_key function, it will become a Key.
     * Masters are a type of option that are not related to keys or flags, and their implementation is completely separate
       The function pclass_set_key returns a pkey type, which is used exclusively for adding specific values.
    */ 

    pkey_set_custom_value ( key, "Value 1" ); // This function adds a specific value to the key, based on the key's type, which in this case is ALW_CUSTOM.
    pkey_set_custom_value ( key, "Value 2" );
    /* What is ALW_CUSTOM?
     * ALW_CUSTOM is a property it gives to a key, allowing only the values you've specified using the pkey_set_custom_value function to be valid. 
     * If the user enters any other text, the pinit_parser function returns a specific error code.
    */

    key = pclass_set_key ( class, 4, ALW_CUSTOM );
    pkey_set_custom_value ( key, "Value1" );
    pkey_set_custom_value ( key, "Value1" );


    pinit_parser ( init, argc, argv );

    {
        int opt_id, i=0;
        
        while ( ( opt_id = pclass_loop_get_opt_id ( class, i ) ) != -1 ) 
        {
            switch ( opt_id )
            {
                case (1): 
                    printf ("this is long_flag\n");
                    break;

                case (2):
                    printf ("this is f\n");
                    break;

                case (3):
                    for ( int vi=0 ; vi < pclass_get_key_size ( class, 3 ) ; ++vi ) // This function returns the count of a key's values.
                    {
                        printf ( "long_key = %s\n", pclass_key_loop_get_value ( class, 3, vi ) ); // This function iterates over the values of a key.
                        /* Its first parameter is the class in which the key opt_id resides.
                         * The second parameter is the option ID that has been converted into the key (or keys).
                         * The third parameter is an index for the iteration (or traversal).
                        */
                    }
                    break;

                case (4):
                    for ( int vi=0 ; vi < pclass_get_key_size ( class, 4 ) ; ++vi )
                    {
                        printf ( "k = %s\n", pclass_key_loop_get_value ( class, 4, vi ) );
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

 $ ./example -f --long_flag --long_key "Value 1"
 this is f
 this is long_flag
 long_key = Value 1

 * The current example does not perform any error handling, so no user errors are issued.
*/