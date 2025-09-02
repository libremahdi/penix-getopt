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

#ifndef PGETOPT_MACRO
#define PGETOPT_MACRO

typedef enum { FLAG, KEY, OBJECT } optmod;
#define EOL { NULL, 0 }

typedef struct { char *option_name; optmod option_mode; } palw;

enum nodmod { PFLAG, PKEY, PNKEY, POBJECT };

struct branch {
    char *name;
    enum nodmod node_mode;
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
    unsigned int class_size;
    struct object **classes;
} popt;
typedef struct object pclass;

popt    *popt_init              ( void ); 
void    pinit_free              ( popt **init );
void    pset_allowed_options    ( pclass **class, palw *alw_opts );

pclass  *pclass_create          ( popt **init, char *name );
void    pclass_free             ( pclass **class );

#endif