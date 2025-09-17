/* Forgiveness is the fragrance that the violet sheds on the heel that has crushed it.
 *  -Mark Twain
*/

#include <stdlib.h>

#ifndef PGETOPT_MACRO
#define PGETOPT_MACRO

typedef struct  { unsigned int option_id; char *option_name; } palw;
typedef struct  { unsigned int error; unsigned int index; } pgoerr;
#define EOL     { 0, NULL } // Indicates the end of the list of allowed options.


enum PKEY_TYPE { ALW_CUSTOM, DENY_CUSTOM, NONE, VOID };



struct alw_branch {
    unsigned int opt_id;
    unsigned int values_size;
    char **values;
    unsigned int names_size;
    char **names;
    enum PKEY_TYPE key_type;
};

struct avl_branch {
    unsigned int opt_id;
    unsigned int values_size;
    char **values;
};

struct object {
    char *name;
    unsigned int alw_size;
    struct alw_branch **alw_tree;
    unsigned int avl_size;
    struct avl_branch **avl_tree;
};


struct init {
    unsigned int classes_size;
    struct object **classes;
};




typedef struct init pinit;
typedef struct object pclass;
typedef struct alw_branch pkey;


pinit          *pinit_create                        ();
void            pinit_free                          ( pinit **init );
void            pinit_set_main_class                ( pinit **init, pclass *class );
pgoerr          pinit_parser                        ( pinit **init, int argc, char **argv );


pclass         *pclass_create                       ( pinit **init, char *name );
void            pclass_free                         ( pclass **class );
void            pclass_set_allowed_options          ( pclass **class, palw *allowed_options );
int             pclass_loop_get_id                  ( pclass  *class, unsigned int index );



pkey            *pclass_set_key                      ( pclass **class, unsigned int opt_id, enum PKEY_TYPE key_type );
unsigned int    pkey_get_key_size                    ( pkey *key );
void            pkey_set_custom_value                ( pkey **key, char *value );
char           *pkey_key_loop_get_value              ( pkey *key, unsigned int index );

/*
*/

// pmaster    *pmaster_create_init         ();
// void        pmaster_set_allowed_names   ( pmaster **mater_init, palw *allowed_names );
// int         pmaster_get_argc            ( int ID );
// int         pmaster_get_argv            ( int ID );
// int         pmaster_get_id              ( pmaster *master_init );
// void        pmaster_free                ( pmaster **master_init );

/*
    pmaster *masters = pmaster_create        ();
    palw masters_list [] = {
        {0, "remove"},
        {1, "create"},
        EOL
    };
    pmaster_set_allowed_names ( &masters, masters_list );
    switch ( pmaster_get_id ( masters ) )
    {
        case 0:
            _remove_exec ( pmaster_get_argc (0), pmaster_get_argv (0) );
            break;
        case 1:
            int a = 1;
            int b = 2;
            ... your code's flow
            break;
    }
            pamster_free (&masters);
*/


#endif