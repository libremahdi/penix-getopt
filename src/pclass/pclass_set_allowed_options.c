/*
 *  Copyright (C) Parabyte Company, All rights reserved.
 *  For more information, please read LICENSE file.
 *
*/
#include <string.h>
#include <stdio.h>

#include "pgetopt.h"
#include "../lib/popt_class.h"
#include "branch.h"
#include "pgetopt_alloc.h"

void pclass_set_allowed_options(pclass *class, palw *allowed_options) {   
    unsigned long int i=0;
    unsigned int repetitive_opt_id = 0;

    while (allowed_options[i].option_name != NULL) {
        if ((repetitive_opt_id = is_alw_tree_repetitive_id (class, allowed_options[i].option_id)) != -1) {
            class->alw_tree[repetitive_opt_id]->names = (char **) pgetopt__realloc ((class->alw_tree[repetitive_opt_id]->names), (sizeof (char *)*(class->alw_tree[repetitive_opt_id]->names_size+1)));
            
            class->alw_tree[repetitive_opt_id]->names[class->alw_tree[repetitive_opt_id]->names_size] = allowed_options[i].option_name;
            ++class->alw_tree[repetitive_opt_id]->names_size;
            internal_add_hint(class->alw_tree[repetitive_opt_id], allowed_options, i);

            ++i;
            continue;
        }
        class->alw_tree = (struct alw_branch **) pgetopt__realloc (class->alw_tree, (sizeof (struct alw_branch *) * (class->alw_size+1)));
        class->alw_tree[class->alw_size] = pgetopt__alloc (sizeof (struct alw_branch));

        class->alw_tree[class->alw_size]->names = pgetopt__alloc (sizeof (char *));

        class->alw_tree[class->alw_size]->names[0] = allowed_options[i].option_name;
        class->alw_tree[class->alw_size]->names_size = 1;

        class->alw_tree[class->alw_size]->opt_id = allowed_options[i].option_id;

        class->alw_tree[class->alw_size]->key_type = VOID;

        class->alw_tree[class->alw_size]->values_size = 0;
        class->alw_tree[class->alw_size]->values = NULL;

        class->alw_tree[class->alw_size]->hints = NULL;
        class->alw_tree[class->alw_size]->hint_size = 0;
        internal_add_hint(class->alw_tree[class->alw_size], allowed_options, i);

        ++i;
        ++class->alw_size;   // also i can write it : class->alw_tree[class->alw_size+i] and remove the ++class->alw_size
                                // ++class->alw_size from here, and put this line in the out of the while segment :
                                // class->alw_size += i;
                                // But it compromises the readability of the code. No?
    }
}
