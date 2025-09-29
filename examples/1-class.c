#include <pgetopt-4.2/pgetopt.h>

int main ( int argc, char **argv )
{
    pinit *init = pinit_create (); // Creating a basic init structure for building the library tree.
    pclass *class = pclass_create ( &init, "main" ); // This function constructs a class instance. The first argument specifies the `init` address, while the second defines the `class` name.

    pclass (&class); // Ensure `pclass` is freed after use to prevent memory leaks.
    pinit_free (&init); // Ensure `pinit` is freed after use to prevent memory leaks.
}