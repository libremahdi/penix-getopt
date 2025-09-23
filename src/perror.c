#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pgetopt.h"
#include "lib/popt_error.h"

static void printerr ( char *err, char *opt )
{
    printf ("Error: %s\n%s\n", opt, err);
}

int pgoerror_parser ( pgoerr _error, char **argv )
{
    return   ( _error.error == _invalid_option      )
    ?   ( printerr ("invalid option.", argv[_error.index]), 1 ) :
             ( _error.error == _key_without_value   )  
    ?   ( printerr ("cant find value for the key.", argv[_error.index]), 1 ) : 
             ( _error.error == _value_syntax_error  )  
    ?   ( printerr ("your value's syntax is not correcy.", argv[_error.index]), 1 ) : 
             ( _error.error == _lack_of_class      )   
    ?   ( printerr ("invalid option", argv[_error.index]), 1 ) : 
             ( _error.error == _class_syntax_error )  
    ?   ( printerr ("invalid option", argv[_error.index]), 1 ) : 
             ( _error.error == _invalid_value )
    ?   ( printerr ("The value is invalid. This value cannot be used.", argv[_error.index]), 1 ) :
             ( _error.error == _lack_of_master )
    ?   ( printerr ("No master was found under this name.", argv[_error.index]), 1 ) :
            0;
}