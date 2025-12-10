#include "pgetopt.h"
#include "salloc.h"
#include "../lib/popt_error.h"

void pinit_set_allowed_masters (pinit *init, palw *allowed_names) {
    unsigned long int i = 0;
    while (allowed_names[i].option_name != NULL) {
        init->alw_masters = (struct master_alw **) realloc (init->alw_masters, (sizeof (struct master_alw *)*(init->alw_masters_size+1)));
        init->alw_masters [init->alw_masters_size] = safe_alloc (sizeof (struct master_alw));
        init->alw_masters [init->alw_masters_size]->name = allowed_names[i].option_name;
        init->alw_masters [init->alw_masters_size]->master_id = allowed_names[i].option_id;
        ++i;
        ++init->alw_masters_size;
    }
}

int pinit_get_master_argc (pinit  *init) {
    return init->avl_master->options_size;
}

char **pinit_get_master_argv (pinit  *init) {
    return init->avl_master->options;
}

char *pinit_get_master_name (pinit  *init) {
    if (init->avl_master == NULL)
        _printerr_pgetopt ("The user has not used any Master, but you want to get the name of the available master!", __LINE__, __FILE__);
    return init->avl_master->name;
}

int pinit_get_master_id (pinit  *init) {
    if (init->avl_master == NULL) return -1;
    return init->avl_master->master_id;
}
