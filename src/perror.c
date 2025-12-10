#include "pgetopt.h"
#include "lib/popt_error.h"

int usererror_parser (usrerr _error, char **argv) {
    return  (_error.error == _invalid_option)
    ?   (_printerr_user ("invalid option.", argv[_error.index]), 1):
            (_error.error == _key_without_value)  
    ?   (_printerr_user ("cant find value for the key.", argv[_error.index]), 1): 
            (_error.error == _lack_of_class)   
    ?   (_printerr_user ("There is no class under this name", argv[_error.index]), 1): 
            (_error.error == _class_syntax_error)  
    ?   (_printerr_user ("invalid class. Pay attention to the structure of the class.\nit should be like that: @[Class_name].[option]", argv[_error.index]), 1):
            (_error.error == _invalid_value)
    ?   (_printerr_user ("The value is invalid. This value cannot be used.", argv[_error.index]), 1):
            (_error.error == _lack_of_master)
    ?   (_printerr_user ("No master was found under this name.", argv[_error.index]), 1): 0;
}