/*
 *  Copyright (C) Parabyte Company, All rights reserved.
 *  For more information, please read LICENSE file.
 *
*/

#include "pgetopt.h"

struct alw_branch {
    unsigned int opt_id;
    unsigned int values_size;
    char **values;
    unsigned int names_size;
    char **names;
    unsigned int hint_size;
    char **hints;
    enum PKEY_TYPE key_type;
};

struct avl_branch {
    unsigned int opt_id;
    unsigned int values_size;
    char **values;
};

struct class {
    char *name;
    unsigned int alw_size;
    struct alw_branch **alw_tree;
    unsigned int avl_size;
    struct avl_branch **avl_tree;
};

struct init {
    unsigned int classes_size;
    struct class **classes;

    struct master_avl *avl_master;

    unsigned int alw_masters_size;
    struct master_alw **alw_masters;

    char *usage;
};
