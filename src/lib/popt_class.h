#ifndef POPT_CLASS
#define POPT_CLASS

static int is_alw_tree_repetitive_id ( pclass *class, unsigned int opt_id )
/* if opt_id already exists, this function returns
 * its index in the pclass structure. Otherwise, return the number -1.
*/ {
    for ( int i = 0 ; i < class->alw_size ; ++i )
        if ( class->alw_tree[i]->opt_id == opt_id ) return i;
    return -1;
}


static int find_char_index ( char *str, char ch, unsigned int chnum )
/* This function finds the index of (chnum)th `ch` character in the string. 
 * example: find_char_index ("Hello.man.man", '.', 1) -> 5
 * example: find_char_index ("Hello.man.man", '.', 2) -> 9
*/ {
    int i=0, n=0;
    while ( str[i] != '\0' )
    {
        if ( str[i] == ch )
        {
            if ( ++n == chnum ) return i;
        }
        ++i;
    }
    return -1;
}


static char *pstr_get_class_name ( char *str )
/* when you insert the 'class.flag' string, this function must return 'class' from the string
*/ {
    char *ret_value = (char *) malloc (sizeof (char) * (strlen (str)+1)); // one character for \0
    strcpy (ret_value, str);
    ret_value[find_char_index (str, '.', 1)]='\0';
    return ret_value;
}


static char *pstr_get_class_value ( char *str )
/* when you insert the 'class.flag' string, this function must return 'flag' from the string.
*/ {
    char *ret_value = strdup ( str + find_char_index (str, '.', 1) + 1 );
    return ret_value;
}


static bool is_class_syntax_correct ( char *str ) {
    unsigned int strln = strlen (str);
    for ( unsigned int i = 0 ; i < strln ; ++i )
    {
        if ( str[i] == '.' )    return true;
    }
    return false;
}

static int get_class_index ( pinit *init, char *class_name ) {
    for ( unsigned int i = 0 ; i < init->classes_size ; ++i )
    {
        if ( strcmp ( init->classes[i]->name, class_name ) == 0 )
            return i;
    }
    return -1;
}

#endif