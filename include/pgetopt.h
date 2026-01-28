/*++
 *  PARABYTE PENIX PGETOPT (PLIBC)
 *  
 *  Copyright (C) 2025-2026 Parabyte Company, All rights reserved.
 * 
 *  Author: Parabyte Company, Parabyte Developer Team (Core)
 *  For more information, please read LICENSE file.
 *--
*/

#include "pstring.h"

#ifndef PENIX__PGETOPT
#define PENIX__PGETOPT

typedef struct { unsigned int option_id; char *option_name; char *option_hint; } palw;
typedef struct { unsigned int error; unsigned int index; } usrerr;
#define EOL { 0, NULL } /* Indicates the end of the list of allowed options. */

enum PKEY_TYPE { ALW_CUSTOM, DENY_CUSTOM, NONE, VOID };

/* must be defined bedore init */
struct alw_branch;
struct avl_branch;
struct class;
struct init;
struct master_alw;
struct master_avl;

typedef struct class pclass;
typedef struct alw_branch pkey;
typedef struct init pinit;


pinit  *pinit_create(char *);
void    pinit_free(pinit *);
void    pinit_set_main_class(pinit *, pclass *);
usrerr  pinit_parser(pinit *, int , char **);
void    pinit_set_allowed_masters(pinit *, palw *);
void    pinit_hint(pinit *);

int     pinit_get_master_argc(pinit *);
char  **pinit_get_master_argv(pinit *);
char   *pinit_get_master_name(pinit *);
int     pinit_get_master_id(pinit *);

int     usererror_parser(usrerr , char **);

pclass *pclass_create(pinit *, char *);
void    pclass_free(pclass *);
void    pclass_set_allowed_options(pclass*, palw*);
int     pclass_loop_get_opt_id(pclass *, unsigned int);

pkey   *pclass_set_key(pclass *, unsigned int, enum PKEY_TYPE);
void    pkey_set_custom_value(pkey *, char *); 
int     pclass_get_key_size(pclass *, unsigned int);
char   *pclass_key_loop_get_value(pclass *, unsigned int, unsigned int);

#endif /* PENIX__PGETOPT */
