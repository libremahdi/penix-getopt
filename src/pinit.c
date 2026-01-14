/*
 *  Copyright (C) Parabyte Company, All rights reserved.
 *  For more information, please read LICENSE file.
 *
*/

#include <stdlib.h>

#include "pgetopt.h"
#include "lib/popt_init.h"
#include "lib/popt_class.h"
#include "lib/popt_error.h"
#include "branch.h"
#include "master.h"
#include "pgetopt_alloc.h"

pinit* pinit_create () {
    pinit *init         = (pinit *) pgetopt__alloc (sizeof (pinit));

    init->classes       = (struct class **) pgetopt__alloc ((sizeof (struct class *)));
    init->classes[0]    = NULL; /* this is the main class */
    init->classes_size  = 1; /* Each pinit by default includes a main class. */
    
    init->alw_masters_size = 0;
    init->avl_master    = NULL;
    init->alw_masters   = NULL;

    return init;
}

void pinit_free (pinit *init) {   
    free (init->classes);

    for (int in_1=0 ; in_1<init->alw_masters_size ; ++in_1) {
        free (init->alw_masters[in_1]);
    }

    free (init->alw_masters);

    if (init->avl_master != NULL) free (init->avl_master->options);
    free (init->avl_master);
    free (init);
}
