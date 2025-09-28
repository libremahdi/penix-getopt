#include <pgetopt-4.2/pgetopt.h>

int main ( int argc, char **argv )
{
    pinit *init = pinit_create (); // Creating a basic init structure for building the library tree.
    pfree (&init); // Ensure `pinit` is freed after use to prevent memory leaks.
}