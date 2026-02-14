/*
 *  Copyright (C) 2025-2026 Mahdi Hosseini Asaad
 *  For more information, please read LICENSE file.
 *
*/

#include <string.h>
#include "pgetopt.h"
#include "branch.h"
#include "master.h"
#include "pgetopt_alloc.h"
#include <stdbool.h>

int is_avl_tree_repetitive_id (pclass *class, unsigned int opt_id)
/* This function searches for opt_id among avl_tree (user options).
 * if it exists, it returns its index in the pclass structure. And if
 * it is not, it returns the number -1!
*/{
    for (int i = 0 ; i < class->avl_size ; ++i)
        if (class->avl_tree[i]->opt_id == opt_id) return i;
    return -1;
}

usrerr _setup_return_usrerr (int ERR_DEFINE, int index, int _LINE__, char* _FILE__) {
    /* Dont remove this printf function. uncomment it only when you want to debug.
    */ // printf ("%d, %s\n", _LINE__, _FILE__); // enable to debung
    usrerr return_err;
    return_err.error=ERR_DEFINE; 
    return_err.index=index;
    return return_err;
}

int IsValueReallyAValue (char *value) 
/* in pgetopt, Values cannot start with '@'. This section is separated
 * in the form of a function so that a certain restriction can be applied
 * in the future!
*/ {
    switch (value[0]) {
        case '@':   return 0;
        case '-':   return 0;    
    }
    return 1;
}

int get_opt_id (pclass *class, char *option) {
    for (int classI=0 ; classI < class->alw_size ; ++classI) {
        for (int valueI=0 ; valueI < class->alw_tree[classI]->names_size ; ++valueI) {
            if (strcmp (class->alw_tree[classI]->names[valueI], option) == 0) {
                return class->alw_tree[classI]->opt_id;
            }
        }
    }
    return -1;
}

int get_master_id (pinit *init, char *name) {
    for (int i = 0 ; i < init->alw_masters_size ; ++i) {
        if (strcmp (init->alw_masters[i]->name, name) == 0) {
            return init->alw_masters[i]->master_id;
        }
    }
    return -1;
}

char **get_master_options (unsigned int _argc, char **_argv, unsigned int index) {
    char **argv = pgetopt__alloc (sizeof (char *) * (_argc - index));
    for (int i = index, j = 0 ; i < _argc ; ++i, ++j) {
        argv[j] = _argv[i];
    }
    return argv;
}

enum PKEY_TYPE get_key_type (pclass *class, int opt_id) {
    for (int i = 0 ; i < class->alw_size ; ++i)
        if (class->alw_tree[i]->opt_id == opt_id) return class->alw_tree[i]->key_type;
    return -1; /* never used */
}

void _phead_flag (pinit **init, unsigned int class_index, unsigned int opt_id) {
    (*init)->classes[class_index]->avl_tree = (struct avl_branch **) pgetopt__realloc (((*init)->classes[class_index]->avl_tree), (sizeof (struct avl_branch *) * ((*init)->classes[class_index]->avl_size + 1)));
    (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size] = pgetopt__alloc (sizeof (struct avl_branch));
    (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size]->opt_id      = opt_id;
    (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size]->values_size = 0;
    (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size]->values      = NULL;
    ++(*init)->classes[class_index]->avl_size;
}

struct avl_branch **get_avl_point (pclass *class, unsigned int opt_id) {
    for (int i = 0 ; i < class->avl_size ; ++i)
        if (class->avl_tree[i]->opt_id == opt_id)
            return &class->avl_tree[i];
    return NULL; /* never used */
}

struct alw_branch **get_alw_point (pclass *class, unsigned int opt_id) {
    for (int i = 0 ; i < class->alw_size ; ++i)
        if (class->alw_tree[i]->opt_id == opt_id)
            return &class->alw_tree[i];
    return NULL; /* never used */
}

bool is_value_allowed (struct alw_branch *alw_tree, char *value) {
    for (int i = 0 ; i < alw_tree->values_size ; ++i) {
        if (strcmp (alw_tree->values[i], value) == 0)
            return true;
    }
    return false;
}

int _phead_key (pinit **init, unsigned int class_index, unsigned int opt_id, char *value) {
    struct alw_branch **alw_key_point = get_alw_point ((*init)->classes[class_index], opt_id);

    if (((*alw_key_point)->key_type == ALW_CUSTOM) && (is_value_allowed ((*alw_key_point), value) == 0))
        return -1;
    if (((*alw_key_point)->key_type == DENY_CUSTOM) && (is_value_allowed ((*alw_key_point), value) == 1))
        return -1;

    (*init)->classes[class_index]->avl_tree = (struct avl_branch **) pgetopt__realloc (((*init)->classes[class_index]->avl_tree), (sizeof(struct avl_branch *)*((*init)->classes[class_index]->avl_size+1)));
    (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size] = pgetopt__alloc (sizeof (struct avl_branch));
    (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size]->opt_id      = opt_id;
    (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size]->values_size = 1;
    (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size]->values      = pgetopt__alloc (sizeof (char *));
    (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size]->values[0]   = value;
    ++(*init)->classes[class_index]->avl_size;

    return 0;
}

int _phead_repetitive_key (pinit **init, unsigned int class_index, unsigned int opt_id, char *value) {
    struct avl_branch **key_point = get_avl_point ((*init)->classes[class_index], opt_id);
    struct alw_branch **alw_key_point = get_alw_point ((*init)->classes[class_index], opt_id);

    if (((*alw_key_point)->key_type == ALW_CUSTOM) && (is_value_allowed ((*alw_key_point), value) == 0))
        return -1;
    if (((*alw_key_point)->key_type == DENY_CUSTOM) && (is_value_allowed ((*alw_key_point), value) == 1))
        return -1;   

    (*key_point)->values   = (char **) pgetopt__realloc ((*key_point)->values, (sizeof (char *)*((*key_point)->values_size+1)));
    (*key_point)->values [(*key_point) -> values_size] = value;
    ++(*key_point)->values_size;

    return 0;
}
