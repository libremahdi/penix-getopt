/*
 * Test File: Clone Option - flag

 * A clone option refers to two or more keys with different names but identical IDs.
 * What are clone options used for?
 * In the structure of Unix-like operating systems, each option has both a short name and a long name:
 * For example, the difference between -o and --output.
 * These two options have exactly the same functionality.

 * In the current commit and this file, Clone Flags can be implemented, but this functionality cannot be 
 * applied to keys at the moment.
*/

#include "pgetopt.h"
#include <stdio.h>


int main ( int argc, char *argv[] )
{
    pinit *init = pinit_create (); // Creating the Entry Point
    // This function initializes the main structure of the Parabyte Getopt parser.


    pclass *class1 = pclass_create (&init, "main"); // Creating the New Class named `main`. you can choose any name
    // This function creates a class. Multiple classes can be created in any desired and unlimited number.


    pinit_set_main_class (&init, class1); // Set the default main class
    /* Any software that uses pgetopt needs to set a custom class as the main class.
     * Any key or flag created in the class associated with the main class can be used in the software without 
     * the need to reference the class name. For more information, refer to the documentation.
    */
    

    palw class1_allowed_options [] = {
    /* Default and Simple Structure for Defining Allowed Options
     * The output, o, and d options all share the same ID: 100.
     * So whenever the user uses the --output, -o, or -d flags, the parser will only parse a single ID.
    
     * The input option is then converted into a key using the pclass_set_key function.
     * In the pgetopt structure, all options are flags by default, unless they are later set as keys using the pclass_set_key function.
    */        
        {"output"   , 100},
        {"d"        , 100},
        {"o"        , 100},
        {"input"    , 101},
        EOL
    };


    pclass_set_allowed_options ( &class1, class1_allowed_options ); // The structure class1_allowed_options is initialized by the pclass_set_allowed_options function.

    pkey key = pclass_set_key ( &class1, 101, NONE); //pkey is an alias for a part of the class structure, and the pclass_set_key function converts a custom option into a key. As mentioned earlier, by default, every option is a flag.

    pclass *user = pclass_create (&init, "user");

    palw user_allowed_options [] = {
        {"output"   , 1},
        {"d"        , 1},
        {"o"        , 1},
        {"input"    , 2},
        EOL
    };
    pclass_set_allowed_options ( &user, user_allowed_options );

    pkey input_key = pclass_set_key ( &user, 1, ALW_CUSTOM);
    pkey_custom_set_value ( &input_key, "Hello" );






    pgoerr err_index = pinit_parse (&init, argc, argv); // pinit_parse is a function for parsing all input arguments and initializing the avl_tree structure.
    /* The function's output is a struct type that returns runtime errors. Errors can either be handled 
     * manually, or they can be delegated to the pgoerror_parser function. The choice is up to the developer.
    */

    /* Manual Error Management
    */

    // if ( err_index.error != 0 )
    // {
        // printf ("Error in %s\n", argv[err_index.index]); 
        // goto err_ret;
    // }

    /* Automatic Error Management
    */
    if ( pgoerror_parser (err_index, argv) ) goto err_ret; // Automatic error parsing



    /* Now we get to the interesting part.

     * The variable opt_id is for the pclass_loop_get function. This function returns the ID of an option 
     * based on its input index. What is the input index variable? It's i.
    */
    int opt_id, i;

    i = 0; // The default value of i for every pclass_loop_get function implemented for each class should be 0.

    while ( ( opt_id = pclass_loop_get ( class1, i ) ) != -1 )
    {
        switch ( opt_id )
        {
            case (100):
                printf ("Class=class1 : flag=output, d or o\n");
                break;
            case (101):
                for ( int in = 0 ; in < pclass_get_key_size ( class1, 101 ) ; ++in ) // pclass_get_key_size returns the total number of values for a key.
                    printf ("Class=class1 : key=input : Value = %s\n", pclass_get_value ( class1, 101, in )); // pclass_get_value returns the values of a key based on the input index.
                break;
        }
        ++i;
    }
    i=0;
    while ( ( opt_id = pclass_loop_get ( user, i ) ) != -1 )
    {
        switch ( opt_id )
        {
            case (1):
                printf ("Class=user : flag=output, d or o\n");
                break;
            case (2):
                for ( int in = 0 ; in < pclass_get_key_size ( user, 2 ) ; ++in )
                    printf ("Class=user : key=input : Value = %s\n", pclass_get_value ( user, 2, in ));
                break;
        }
        ++i;
    }


err_ret:
    pclass_free (&class1);
    pclass_free (&user);
    pinit_free (&init);
    return 0;
}

