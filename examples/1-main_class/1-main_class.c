#include <pgetopt-4.3/pgetopt.h>

int main ( int argc, char **argv )
{
    pinit *init = pinit_create ();
    pclass *class = pclass_create ( init, "main" ); // This function constructs a class instance. The first argument specifies the `pinit` address, while the second defines the `class` name.

    pinit_set_main_class ( init, class ); // This function sets a class as the main class.

    pclass_free (class); // Ensure `pclass` is freed after use to prevent memory leaks.
    pinit_free (init);
}

/* Example Export :
 * The execution of the software should not produce any output.
*/