/* Forgiveness is the fragrance that the violet sheds on the heel that has crushed it.
 *  -Mark Twain
*/

#include <stdlib.h>

#ifndef PGETOPT_MACRO
#define PGETOPT_MACRO

typedef struct  { unsigned int option_id; char *option_name; } palw;
typedef struct  { unsigned int error; unsigned int index; } pgoerr;
#define EOL     { 0, NULL } // Indicates the end of the list of allowed options.


enum PKEY_TYPE { INT, STR, ALW_CUSTOM, DENY_CUSTOM, NONE, PFLAG };



struct alw_branch {
    unsigned int opt_id;
    unsigned int values_size;
    char **values;
    unsigned int names_size;
    char **names;
    enum PKEY_TYPE key_type;
};

struct avl_branch {
    unsigned int ID;
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
typedef struct object pclass;

typedef struct init {
    unsigned int classes_size;
    struct object **classes;
} pinit;





pinit      *pinit_create                ();
void        pinit_free                  ( pinit **init );

pclass     *pclass_create               ( pinit **init, char *name );
void        pclass_free                 ( pclass **class );
void        pclass_set_allowed_options  ( pclass **class, palw *allowed_options );



#endif