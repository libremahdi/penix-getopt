#include <pgetopt-4.2/pgetopt.h>

int main ( int argc, char **argv )
{
    pinit *init = pinit_create ();
    
    pclass *class = pclass_create ( init, "main" );
    
    pinit_set_main_class ( init, class );

    palw main_allowed_options [] = 
    /* `palw` is a type of variable, and `main_allowed_options` is an arbitrary (or custom) variable name. 
     * Its components are an ID and a parameter name.
    */ {
    //  { opt_id, opt_name },
        { 1, "long_flag" },
        { 2, "f" },
        EOL
    };

    pclass_set_allowed_options ( class, main_allowed_options ); // This function assigns a PALW to a class.

    pclass_free (class);
    pinit_free (init);
}

/* Example Export :
 * The execution of the software should not produce any output.
*/