#include <stdlib.h>
#include <string.h>

#ifndef POPT_CLASS
#define POPT_CLASS


static unsigned int find_char_index ( char *str, char ch, unsigned int chnum )
{
    int i=0;
    int n=0;
    while ( str[i] != '\0' )
    {
        if ( str[i] == ch )
        {
            ++n;
            if ( n == chnum ) return i;
        }
        ++i;
    }
    return -1;
}


static char *pstr_get_class ( char *str )
{
    char *ret_value = (char *) malloc (sizeof (char) *  (find_char_index (str, '.', 1)+1)); // one character for \0
    strcpy (ret_value, str);
    ret_value[find_char_index (str, '.', 1)]='\0';
    return ret_value;
}

static unsigned int get_class_index ( pinit *init, char *class_name )
{
}
#endif