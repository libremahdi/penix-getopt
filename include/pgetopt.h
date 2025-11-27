/* Forgiveness is the fragrance that the violet sheds on the heel that has crushed it.
 *  -Mark Twain
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __PARABYTE_PGETOPT__
#define __PARABYTE_PGETOPT__

typedef struct  { unsigned int option_id; char *option_name; } palw;
typedef struct  { unsigned int error; unsigned int index; } usrerr;
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
struct class {
    char *name;
    unsigned int alw_size;
    struct alw_branch **alw_tree;
    unsigned int avl_size;
    struct avl_branch **avl_tree;
};

struct master_alw {
    char *name;
    unsigned int master_id;
};

struct master_avl {
    char *name;
    unsigned int master_id;
    unsigned int options_size;
    char **options;
};

struct init {
    unsigned int classes_size;
    struct class **classes;

    struct master_avl *avl_master;

    unsigned int alw_masters_size;
    struct master_alw **alw_masters;

};




typedef struct init pinit;
typedef struct class pclass;
typedef struct alw_branch pkey;

pinit          *pinit_create                        ();
void            pinit_free                          ( pinit *init );
void            pinit_set_main_class                ( pinit *init, pclass *class );
usrerr          pinit_parser                        ( pinit *init, int argc, char **argv );
void            pinit_set_allowed_masters           ( pinit *init, palw *allowed_names );

int             pinit_get_master_argc               ( pinit  *init );
char          **pinit_get_master_argv               ( pinit  *init );
char           *pinit_get_master_name               ( pinit  *init );
int             pinit_get_master_id                 ( pinit  *init );

int             usererror_parser                    ( usrerr _error, char **argv );



pclass         *pclass_create                       ( pinit **init, char *name );
void            pclass_free                         ( pclass **class );
void            pclass_set_allowed_options          ( pclass **class, palw *allowed_options );
int             pclass_loop_get_opt_id              ( pclass  *class, unsigned int index );

pkey            *pclass_set_key                     ( pclass **class, unsigned int opt_id, enum PKEY_TYPE key_type );
void            pkey_set_custom_value               ( pkey **key, char *value );
unsigned int    pclass_get_key_size                 ( pclass  *class, unsigned int opt_id );
char           *pclass_key_loop_get_value           ( pclass  *class, unsigned int opt_id, unsigned int index );


#endif // __PARABYTE_PGETOPT__