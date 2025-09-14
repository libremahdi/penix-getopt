#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#include "pgetopt.h"
#include "lib/popt_tree.h"
#include "lib/popt_class.h"
#include "lib/popt_key.h"

pinit* pinit_create ()
{
    pinit *init          = (pinit *) malloc (sizeof (pinit));
    init->classes_index = 0;

    init->classes = (struct object **) malloc ( ( sizeof (struct object *) ) );
    init->classes[0] = NULL; // this is the main class
    return init;
}

pgoerr pinit_parse ( pinit **init, int argc, char **argv )
{
    char *char2strv = NULL;

    pgoerr _return;
    unsigned int class_index;    
    char *class_name = NULL;
    char *class_value = NULL;

    struct branch **key_point;

    for ( int i = 1 ; i < argc ; ++i )
    {
        if ( argv[i][0] == '-' && argv[i][1] != '-' )
        {
            if ( strlen (argv[i]) == 2 )
            {
                char2strv = strdup (argv[i]+1);
                switch ( is_alw ((*init)->classes[0], char2strv) )
                {
                    case -1:
                        free (char2strv);
                        _return.index = i;
                        _return.error = 1;
                        return _return;
                    case 0:
                            if ( is_repetitive ( (*init)->classes[0], char2strv ) == true )   continue;
                            (*init)->classes[0]->avl_tree = ( struct branch **) realloc ( ((*init)->classes[0]->avl_tree), ( sizeof (struct branch *) * ( (*init)->classes[0]->avl_size + 1 )) );
                            (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size] = ( struct branch * ) malloc ( sizeof ( struct branch ) );
                            (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->name          = char2strv;
                            (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->ID            = what_is_ID ((*init)->classes[0], char2strv);
                            (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values_size   = 0;
                            (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values        = NULL;
                            ++(*init)->classes[0]->avl_size;
                            break;
                    default:
                        if ( i+1 >= argc )
                        {
                            _return.index = i;
                            _return.error = 1;
                            return _return;
                        }
                        if ( is_value_alw ( argv[i+1]) )
                        {
                            _return.index = i;
                            _return.error = 1;
                            return _return;
                        }
                        
                        if ( is_repetitive ( (*init)->classes[0], char2strv ) == false )
                        {
                            (*init)->classes[0]->avl_tree = ( struct branch **) realloc ( ((*init)->classes[0]->avl_tree), ( sizeof (struct branch *) * ( (*init)->classes[0]->avl_size + 1 )) );
                            (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size] = ( struct branch * ) malloc ( sizeof ( struct branch ) );
                            (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->name          = char2strv;
                            (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->ID            = what_is_ID ((*init)->classes[0], char2strv);
                            (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values_size   = 1;
                            (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values        = ( char ** ) malloc ( sizeof (char *) );
                            (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values[0]     = ( char * ) malloc ( sizeof (char) * ( strlen (argv[i+1]) + 1 ) );
                            strcpy ( (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values[0], argv[i+1]);
                            ++(*init)->classes[0]->avl_size;
                            ++i;
                            break;
                        }
                        key_point=get_point ((*init)->classes[0], char2strv);
                        (*key_point)->values   = ( char ** ) realloc ( (*key_point)->values, (sizeof (char *) * ((*key_point)->values_size+1)));
                        (*key_point)->values [(*key_point) -> values_size] = ( char * ) malloc ( sizeof (char) * ( strlen (argv[i+1]) + 1 ) );
                        strcpy ( (*key_point)->values [(*key_point) -> values_size], argv[i+1]);
                        ++(*key_point) -> values_size;
                        ++i;
                        free (char2strv);
                        break;
                }
            }
            else
            {
                for ( int j = 1 ; j <=strlen (argv[i])-1 ; ++j )
                {
                    char2strv = (char *) malloc (sizeof (char)*2);
                    char2strv[0]=argv[i][j];
                    char2strv[1]='\0';
                    switch ( is_alw ((*init)->classes[0], char2strv) )
                    {
                        case -1:
                            free (char2strv);
                            _return.index = i;
                            _return.error = 1;
                            return _return;
                        case 0:
                            if ( is_repetitive ( (*init)->classes[0], char2strv ) == true )   continue;
                            (*init)->classes[0]->avl_tree = ( struct branch **) realloc ( ((*init)->classes[0]->avl_tree), ( sizeof (struct branch *) * ( (*init)->classes[0]->avl_size + 1 )) );
                            (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size] = ( struct branch * ) malloc ( sizeof ( struct branch ) );
                            (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->name          = char2strv;
                            (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->ID            = what_is_ID ((*init)->classes[0], char2strv);
                            (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values_size   = 0;
                            (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values        = NULL;
                            ++(*init)->classes[0]->avl_size;
                            break;
                    }
                }
            }

        }
        else if ( argv[i][0] == '-' && argv[i][1] == '-' )
        {
            char2strv = strdup (argv[i]+2);

            switch ( is_alw ((*init)->classes[0], char2strv) )
            {
                case -1:
                    free (char2strv);
                    _return.index = i;
                    _return.error = 1;
                    return _return;
                case 0:
                        if ( is_repetitive ( (*init)->classes[0], char2strv ) == true )   continue;
                        (*init)->classes[0]->avl_tree = ( struct branch **) realloc ( ((*init)->classes[0]->avl_tree), ( sizeof (struct branch *) * ( (*init)->classes[0]->avl_size + 1 )) );
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size] = ( struct branch * ) malloc ( sizeof ( struct branch ) );
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->name          = char2strv;
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->ID            = what_is_ID ((*init)->classes[0], char2strv);
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values_size   = 0;
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values        = NULL;
                        ++(*init)->classes[0]->avl_size;
                        break;
                default:
                    if ( i+1 >= argc )
                    {
                        _return.index = i;
                        _return.error = 1;
                        return _return;
                    }
                    if ( is_value_alw ( argv[i+1]) )
                    {
                        _return.index = i;
                        _return.error = 1;
                        return _return;
                    }
                    
                    if ( is_repetitive ( (*init)->classes[0], char2strv ) == false )
                    {
                        (*init)->classes[0]->avl_tree = ( struct branch **) realloc ( ((*init)->classes[0]->avl_tree), ( sizeof (struct branch *) * ( (*init)->classes[0]->avl_size + 1 )) );
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size] = ( struct branch * ) malloc ( sizeof ( struct branch ) );
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->name          = char2strv;
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->ID            = what_is_ID ((*init)->classes[0], char2strv);
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values_size   = 1;
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values        = ( char ** ) malloc ( sizeof (char *) );
                        (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values[0]     = ( char * ) malloc ( sizeof (char) * ( strlen (argv[i+1]) + 1 ) );
                        strcpy ( (*init)->classes[0]->avl_tree[(*init)->classes[0]->avl_size]->values[0], argv[i+1]);
                        ++(*init)->classes[0]->avl_size;
                        ++i;
                        break;
                    }
                    key_point=get_point ((*init)->classes[0], char2strv);
                    (*key_point)->values   = ( char ** ) realloc ( (*key_point)->values, (sizeof (char *) * ((*key_point)->values_size+1)));
                    (*key_point)->values [(*key_point) -> values_size] = ( char * ) malloc ( sizeof (char) * ( strlen (argv[i+1]) + 1 ) );
                    strcpy ( (*key_point)->values [(*key_point) -> values_size], argv[i+1]);
                    ++(*key_point) -> values_size;
                    ++i;
                    free (char2strv);
                    break;
            }
        }
        else if ( argv[i][0] == '@' )
        {
            char2strv   = strdup (argv[i]+1);
            class_name  = pstr_get_class_name (char2strv);
            class_value = pstr_get_class_value (char2strv);
            if ( (class_index = get_class_index ((*init), class_name)) == -1 ) 
            {
                free (class_name);
                free (class_value);
                free (char2strv);
                _return.index = i;
                _return.error = 1;
                return _return;
            }
            free (class_name);
            free (char2strv);

            switch ( is_alw ((*init)->classes[class_index], class_value) )
            {
                case -1:

                    free (class_value);
                    _return.index = i;
                    _return.error = 1;
                    return _return;
                case 0:
                        if ( is_repetitive ( (*init)->classes[class_index], class_value ) == true )   continue;
                        (*init)->classes[class_index]->avl_tree = ( struct branch **) realloc ( ((*init)->classes[class_index]->avl_tree), ( sizeof (struct branch *) * ( (*init)->classes[class_index]->avl_size + 1 )) );
                        (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size] = ( struct branch * ) malloc ( sizeof ( struct branch ) );
                        (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size]->name          = class_value;
                        (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size]->key_type      = -1;
                        (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size]->ID            = what_is_ID ((*init)->classes[class_index], class_value);
                        (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size]->values_size   = 0;
                        (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size]->values        = NULL;
                        ++(*init)->classes[class_index]->avl_size;
                        break;  
            }
        }
    }
    _return.index = -1;
    _return.error = 0;
    return _return;
}

void pinit_set_main_class ( pinit **init, pclass *class )
{
    (*init)->classes[0] = class;
}


void pinit_free ( pinit **init )
{
    free ((*init)->classes);
    free (*init);
}



