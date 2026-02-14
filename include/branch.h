/*
 *  Copyright (C) 2025-2026 Mahdi Hosseini Asaad
 *  For more information, please read LICENSE file.
 *
*/

#include "pgetopt.h"

/* This structure is repeated for each of the allowed options. 
 * That is, each option essentially has the same structure that holds the valid and invalid information 
   along with the hints.
*/ struct alw_branch {
    unsigned int opt_id;
    unsigned int values_size;
    char **values;
    unsigned int names_size;
    char **names;
    unsigned int hint_size;
    char **hints;
    enum PKEY_TYPE key_type;
};

/* The options that the parser has deemed valid and generated no errors for are 
   accommodated within this structure for traversal by the corresponding functions.
   
 | Please also review the comment related to the struct class.
*/ struct avl_branch { 
    unsigned int opt_id;
    unsigned int values_size;
    char **values;
};

/* Classes contain all user inputs  and valid options (palw_branch). The parser compares these two, 
   and if any option or value in alw_branch is invalid, it generates an error. Otherwise, 
   it loads avl_branch for traversal by the corresponding functions (e.g., pclass_loop_get_opt_id / pclass_key_loop_get_value).
*/ struct class {
    char *name;
    unsigned int alw_size;
    struct alw_branch **alw_tree;
    unsigned int avl_size;
    struct avl_branch **avl_tree;
};

/* It holds all classes, masters, and the main hint text of the program. 
 * It serves as the foundation of the entire pgetopt library.
*/ struct init {
    unsigned int classes_size;
    struct class **classes;

    struct master_avl *avl_master;

    unsigned int alw_masters_size;
    struct master_alw **alw_masters;

    char *usage;
};
