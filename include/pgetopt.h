#ifndef PGETOPT_MACRO
#define PGETOPT_MACRO

struct init {
    char *name[16];
    struct init **branches;
};

typedef struct root {
    char **avl_flags;
    char **avl_keys;
    struct init *tree;
} popt;

popt *popt_init (void);
int  popt_parse ( popt *root, int argc, char *argv[] );
char ploop_get_flags ( popt root, unsigned long int *i );

#endif