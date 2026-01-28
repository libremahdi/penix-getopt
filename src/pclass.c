/*
 *  Copyright (C) Parabyte Company, All rights reserved.
 *  For more information, please read LICENSE file.
 *
*/

#include <stdlib.h>
#include "pgetopt.h"
#include "branch.h"
#include "pgetopt_alloc.h"

pclass* __attribute__((nonnull, warn_unused_result, malloc))
pclass_create (pinit *init, char *name) {    
    init->classes = pgetopt__realloc (init->classes,(sizeof(struct class *)*(init->classes_size+1)));

    init->classes[init->classes_size] = pgetopt__alloc (sizeof (struct class));
    init->classes[init->classes_size]->name = name;
    
    init->classes[init->classes_size]->alw_size = 0;
    init->classes[init->classes_size]->avl_size = 0;

    init->classes[init->classes_size]->alw_tree = NULL;
    init->classes[init->classes_size]->avl_tree = NULL;

    return init->classes[init->classes_size++];
}

void __attribute__((nonnull))
pclass_free (pclass *class) {
    // ALW Frees
    for (int i = 0 ; i < class->alw_size ; ++i) {
        for (int in_2=0 ; in_2<class->alw_tree[i]->hint_size ; ++in_2) {
            free (class->alw_tree[i]->hints[in_2]);
        }
        free (class->alw_tree[i]->names);
        free (class->alw_tree[i]->hints);
        free (class->alw_tree[i]->values);
        free (class->alw_tree[i]);
    }
    free (class->alw_tree);

    // AVL Frees
    for (int i = 0 ; i < class->avl_size ; ++i) {
        free (class->avl_tree[i]->values);
        free (class->avl_tree[i]);
    }
    free (class->avl_tree);
    free (class);
}
