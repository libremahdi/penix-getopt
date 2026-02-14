/*
 *  Copyright (C) Mahdi Hosseini Asaad, All rights reserved.
 *  For more information, please read LICENSE file.
 *
*/

#ifndef PGETOPT__POPT_INIT
#define PGETOPT__POPT_INIT

#include "pgetopt.h"
#include <stdbool.h>

/* This function searches for opt_id among avl_tree (user options).
 * if it exists, it returns its index in the pclass structure. And if
 * it is not, it returns the number -1!
*/ int is_avl_tree_repetitive_id (pclass *, unsigned int);

usrerr _setup_return_usrerr (int, int, int, char*);

/* in pgetopt, Values cannot start with '@'. This section is separated
 * in the form of a function so that a certain restriction can be applied
 * in the future!
*/ int IsValueReallyAValue (char *);

int get_opt_id (pclass *, char *);

int get_master_id (pinit *, char *);

char **get_master_options (unsigned int, char **, unsigned int);

enum PKEY_TYPE get_key_type (pclass *, int);

void _phead_flag (pinit **, unsigned int, unsigned int);

struct avl_branch **get_avl_point (pclass *, unsigned int);

struct alw_branch **get_alw_point (pclass *, unsigned int);

bool is_value_allowed (struct alw_branch *, char *);

int _phead_key (pinit **, unsigned int, unsigned int, char *);

int _phead_repetitive_key (pinit **, unsigned int, unsigned int, char *);

#endif /* PGETOPT__POPT_INIT */
