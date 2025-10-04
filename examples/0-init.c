#include <pgetopt-4.2/pgetopt.h>

int main ( int argc, char **argv ) {
    pinit *init = pinit_create (); // Creating a basic init structure for building the library tree.
    pinit_free (&init); // Ensure `pinit` is freed after use to prevent memory leaks.
}

/* Example Export :
 * The execution of the software should not produce any output.
*/