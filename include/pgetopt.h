/* Forgiveness is the fragrance that the violet sheds on the heel that has crushed it.
 *  -Mark Twain
*/

#include <stdlib.h>

#ifndef PGETOPT_MACRO
#define PGETOPT_MACRO

typedef struct  { char *option_name; unsigned int ID; } palw;
#define EOL     { NULL, 0 } // Indicates the end of the list of allowed options.

enum PKEY_TYPE { INT, STR, ALW_CUSTOM, DENY_CUSTOM, NONE }; // -1 for flags

struct branch {
    char *name;
    unsigned int ID;
    enum PKEY_TYPE key_type; // if the option is a flag, this variable remains -1
    unsigned int values_size;
    char **values;
};

struct object {
    char *name;
    unsigned int alw_size;
    struct branch **alw_tree;
    unsigned int avl_size;
    struct branch **avl_tree;
};

typedef struct init {
    unsigned int classes_index;
    struct object **classes;
} pinit;
typedef struct object pclass;


pinit* pinit_create             ( );
void    pinit_free              ( pinit **init );
void    pinit_set_main_class    ( pinit **init, pclass *class );
int     pinit_parse             ( pinit **init, int argc, char **argv );


pclass  *pclass_create          ( pinit  **init, char *name );
void    pclass_free             ( pclass **class );
void pclass_set_allowed_options ( pclass **class, palw *alw_opts );
int     pclass_loop_get         ( pclass  *class, unsigned int opt_id );

typedef struct branch *pkey;
pkey    pclass_set_key          ( pclass **class, unsigned int KEY_ID, enum PKEY_TYPE key_type );

void    pkey_set_custom_value   ( pkey *KEY, char *value );


#endif