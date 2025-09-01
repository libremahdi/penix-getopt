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


// Available Options segment
enum nodmod { PFLAG, PKEY, PNKEY, POBJECT }; 
struct init {
    char *name;
    enum nodmod node_mode;
    char **branches;
};

typedef struct root {
    unsigned int alw_size;
    struct init **alw_tree; // a tree of Available options tree
    unsigned int avl_size;
    struct init **avl_tree; // a tree of Allowed options tree
} popt;
// end segment




popt*   popt_init       ( void ); // This function initializes all members of the root data structure.
void    pset_alw_opts   ( popt **root, palw *alw_opts );
void    pfree           ( popt **root );

#endif