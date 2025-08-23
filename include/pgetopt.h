#ifndef PGETOPT_MACRO
#define PGETOPT_MACRO

struct init {
    char *name[16];
    struct init **branches;
};

typedef struct root {
    unsigned long int flags_num;
    unsigned long int keys_num;
    char **avl_flags;
    char **avl_keys;
    struct init *tree;
} popt;

popt *popt_init (void);
int  popt_parse ( popt **root, int argc, char *argv[] );
char ploop_get_flags ( popt root, unsigned long int *i );
void pfree ( popt **root );
#endif