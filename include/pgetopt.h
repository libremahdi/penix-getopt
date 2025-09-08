/*  Manual of General Architecture
    At the initial stage, pgetopt must be initialized with a structure  
    containing all valid options and their respective types. Subsequently,  
    if the developer deems it necessary, they may define which values are  
    allowed or disallowed for each key or object. For example, they can  
    specify that the type key may only accept the values file and folder,  
    or alternatively, mark those values as invalid.

    For objects, the process differs slightly. It is mandatory for the  
    developer to specify which keys and flags each object can accept.  
    After that, they may define which values are permitted or prohibited  
    for each subobject key.
*/

#include <stdlib.h>

#ifndef PGETOPT_MACRO
#define PGETOPT_MACRO

typedef enum    { FLAG, KEY, OBJECT } optmod;
typedef struct  { char *option_name; optmod option_mode; unsigned int ID; } palw;
#define EOL     { NULL, 0 } // Indicates the end of the list of allowed options.


struct branch {
    char *name;
    optmod node_mode;
    unsigned int ID;
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


pinit*  pinit_create            (); 
void    pinit_free              ( pinit **init );
void    pinit_set_main_class    ( pinit **init, pclass *class );
int     pinit_parse             ( pinit **init, int argc, char **argv );

pclass  *pclass_create          ( pinit  **init, char *name );
void    pclass_free             ( pclass **class );
void pclass_set_allowed_options ( pclass **class, palw *alw_opts );
int     pclass_loop_get         ( pclass  *class, unsigned int opt_id );

#endif