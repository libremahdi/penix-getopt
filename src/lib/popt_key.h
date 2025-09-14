#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef POPT_KEY
#define POPT_KEY

static int is_value_alw ( char *str )
{
    if ( (str[0] == '-') || (str[0] == ',') ) return 1;
    return 0;   
}
    
#endif