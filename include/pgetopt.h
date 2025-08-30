#ifndef PGETOPT_MACRO
#define PGETOPT_MACRO



typedef enum {
    flag, key
} optmod;

struct init {
    char *name;
    char **branches;
};

typedef struct root {
    unsigned long int flags_num;
    unsigned long int keys_num;
    unsigned long int avl_flags_num; // available flags number
    unsigned long int avl_keys_num;  // available keys number
    char **avl_flags; // available flags array pointer
    char **avl_keys;  // available keys array pointer
    struct init **tree;
} popt;

#define EOL {NULL, 0} // Indicates the end of the list of allowed options.
#define EOO -1        // Indicates the end of this list of argument options.

typedef struct {
    char *opts;
    optmod option_mode;
} pavl;


popt *popt_init (void);
char *popt_parse ( popt **root, const int argc, char *argv[] );
void pset_avl_opts ( popt **root, pavl *avl_opts );
void pfree ( popt **root );


char ploop_get_flags ( popt *root, unsigned long int i );
#endif