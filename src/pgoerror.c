#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pgetopt.h"
#include "lib/popt_error.h"

int pgoerror_parser ( pgoerr _error, char **argv )
{
    switch (_error.error)
    {
        case _invalid_option:
            printf ("Error in `%s` : This option is not exist.\n", argv[_error.index]);
            break;
        case _key_without_value:
            printf ("Error in `%s` : This option is a key and takes a value.\n", argv[_error.index]);
            break;
        case _value_syntax_error:
            printf ("Error in `%s` : Values cannot start with `@` and `-`.\n", argv[_error.index]);
            break;
        case _lack_of_class:
            printf ("Error in `%s` : No class was found under this name.\n", argv[_error.index]);
            break;
        case _class_syntax_error:
            printf ("Error in `%s` : class syntax is not correct.\n", argv[_error.index]);
            break;
        case _without_error:
            return 0;
    }
    return 1;
}
