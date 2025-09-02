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

typedef enum { FLAG, KEY, OBJECT } optmod; // This is defined to assign the functionality of each option.
#define EOL { NULL, 0 } // To indicate the end of the list of `option functionalities`.

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
    struct branch **alw_tree; // a tree of Available options tree
    unsigned int avl_size;
    struct branch **avl_tree; // a tree of Allowed options tree
};

typedef struct init {
    unsigned int class_size;
    struct object **classes;
} popt; // Parabyte Option


popt*   popt_init       ( void ); // This function initializes all members of the root data structure.
void    pclass_create   ( popt **main, char *name );
void    pfree           ( popt **main );
#endif