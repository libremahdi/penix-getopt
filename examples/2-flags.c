#include <pgetopt-4.2/pgetopt.h>

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

    pclass_free (&class); // Ensure `pclass` is freed after use to prevent memory leaks.
    pinit_free (&init); // Ensure `pinit` is freed after use to prevent memory leaks.
}

/* Example Export :
 * The execution of the software should not produce any output.
*/