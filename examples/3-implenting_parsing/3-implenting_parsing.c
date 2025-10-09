#include <pgetopt-4.2/pgetopt.h>

#include <stdio.h> // just for printf :)

int main ( int argc, char **argv )
{
    pinit *init = pinit_create (); // Creating a basic init structure for building the library tree.
    
    pclass *class = pclass_create ( &init, "main" ); // This function constructs a class instance. The first argument specifies the `init` address, while the second defines the `class` name.
    
    pinit_set_main_class ( &init, class ); // This function sets a class as the main class.
    /* The class that is set as main does not need to be explicitly referenced (or qualified) to use its parameters.
    */

    palw main_allowed_options [] = 
    /* `palw` is a type of variable, and `main_allowed_options` is an arbitrary (or custom) variable name. 
     * Its components are an ID and a parameter name.
    */ {
    //  { opt_id, opt_name },
        { 1, "long_flag" },
        { 2, "f" },
        EOL
    };

    pclass_set_allowed_options ( &class, main_allowed_options ); // This function assigns a PALW to a class.
                                                                 // The function's return value is of type usrerr.
    pinit_parser ( &init, argc, argv ); // As its name suggests, this function performs part of the parsing operation.
    /* Specifically, this function initializes (or populates) the PAVl structure with the values consisting 
       of the arguments entered by the user.
    */

    { // `pclass *class` parsing segment
        int opt_id, i=0;
        
        while ( ( opt_id = pclass_loop_get_opt_id ( class, i ) ) != -1 ) // this function returns the option ID of the options used by the user
        /* The function pclass_loop_get_opt_id iterates over (or traverses) the PAVl structure.
         * Its first argument is the corresponding class, and the second argument is an index 
           that helps with the PAVl traversal
         
         * If there is no data to traverse, the function returns a value of -1.
           ( Option IDs are always a positive number. )
         */ {
            switch ( opt_id )
            {
                case (1): // The number 1 is merely a simple identifier of option! (opt_id).
                    printf ("this is long_flag\n");
                    break;
                case (2):
                    printf ("this is f\n");
                    break;
            }
            ++i;
        }
    }
    
    pclass_free (&class); // Ensure `pclass` is freed after use to prevent memory leaks.
    pinit_free (&init); // Ensure `pinit` is freed after use to prevent memory leaks.
}

/* Example Export :
 * If you provide no arguments to the software, you should see no output.

 $ ./example -f --long_flag
 this is f
 this is long_flag

 * The current example does not perform any error handling, so no user errors are issued.
*/