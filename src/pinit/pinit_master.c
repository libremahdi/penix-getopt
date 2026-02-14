/*
 *  Copyright (C) 2025-2026 Mahdi Hosseini Asaad
 *  For more information, please read LICENSE file.
 *
*/

#include "pgetopt.h"
#include "branch.h"
#include "../lib/popt_error.h"
#include "master.h"
#include "pgetopt_alloc.h"

void __attribute__((nonnull))
pinit_set_allowed_masters (pinit *init, palw *allowed_names) {
    unsigned long int i = 0;
    while (allowed_names[i].option_name != NULL) {
        init->alw_masters = (struct master_alw **) pgetopt__realloc (init->alw_masters, (sizeof (struct master_alw *)*(init->alw_masters_size+1)));
        init->alw_masters [init->alw_masters_size] = pgetopt__alloc (sizeof (struct master_alw));
        init->alw_masters [init->alw_masters_size]->name = allowed_names[i].option_name;
        init->alw_masters [init->alw_masters_size]->master_id = allowed_names[i].option_id;

        if (allowed_names[i].option_hint==NULL) 
            init->alw_masters [init->alw_masters_size]->hint=NULL;
        else 
            init->alw_masters [init->alw_masters_size]->hint = allowed_names[i].option_hint;

        ++i;
        ++init->alw_masters_size;
    }
}

int __attribute__((nonnull))
pinit_get_master_argc (pinit  *init) {
    return init->avl_master->options_size;
}

char** __attribute__((nonnull))
pinit_get_master_argv (pinit  *init) {
    return init->avl_master->options;
}

char* __attribute__((nonnull))
pinit_get_master_name (pinit  *init) {
    if (init->avl_master == NULL)
        pgetopt__printerr ("The user has not used any Master, but you want to get the name of the available master!", __LINE__, __FILE__);
    return init->avl_master->name;
}

int __attribute__((nonnull))
pinit_get_master_id (pinit  *init) {
    if (init->avl_master == NULL) return -1;
    return init->avl_master->master_id;
}
