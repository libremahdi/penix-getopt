#ifndef PENIX__PGETOPT
#define PENIX__PGETOPT

typedef struct { unsigned int option_id; char *option_name; } palw;
typedef struct { unsigned int error; unsigned int index; } usrerr;
#define EOL { 0, NULL } /* Indicates the end of the list of allowed options. */

enum PKEY_TYPE { ALW_CUSTOM, DENY_CUSTOM, NONE, VOID };

struct alw_branch;
struct avl_branch;
struct class;
struct init;

struct master_alw;
struct master_avl;

typedef struct init pinit;
typedef struct class pclass;
typedef struct alw_branch pkey;

pinit  *pinit_create();
void    pinit_free(pinit *init);
void    pinit_set_main_class(pinit *init, pclass *class);
usrerr  pinit_parser(pinit *init, int argc, char **argv);
void    pinit_set_allowed_masters(pinit *init, palw *allowed_names);

int     pinit_get_master_argc(pinit *init);
char  **pinit_get_master_argv(pinit *init);
char   *pinit_get_master_name(pinit *init);
int     pinit_get_master_id(pinit *init);

int     usererror_parser(usrerr _error, char **argv);

pclass *pclass_create(pinit *init, char *name);
void    pclass_free(pclass *class);
void    pclass_set_allowed_options(pclass *class, palw *allowed_options);
int     pclass_loop_get_opt_id(pclass *class, unsigned int index);

pkey   *pclass_set_key(pclass *class, unsigned int opt_id, enum PKEY_TYPE key_type);
void    pkey_set_custom_value(pkey *key, char *value);
unsigned 
int     pclass_get_key_size(pclass *class, unsigned int opt_id);
char   *pclass_key_loop_get_value(pclass *class, unsigned int opt_id, unsigned int index);


#endif /* PENIX__PGETOPT */