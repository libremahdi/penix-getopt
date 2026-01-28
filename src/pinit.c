/*
 *  Copyright (C) Parabyte Company, All rights reserved.
 *  For more information, please read LICENSE file.
 *
*/

#include <stdlib.h> /* free */
#include <stdio.h> /* printf */
#include <string.h> /* strlen */

#include "pgetopt.h"
#include "lib/popt_init.h"
#include "lib/popt_class.h"
#include "lib/popt_error.h"
#include "branch.h"
#include "master.h"
#include "pgetopt_alloc.h"

pinit* __attribute__((warn_unused_result, malloc))
pinit_create (char *usage) {
    pinit *init         = (pinit *) pgetopt__alloc (sizeof (pinit));

    init->classes       = (struct class **) pgetopt__alloc ((sizeof (struct class *)));
    init->classes[0]    = NULL; /* this is the main class */
    init->classes_size  = 1; /* Each pinit by default includes a main class. */
    
    init->alw_masters_size = 0;
    init->avl_master    = NULL;
    init->alw_masters   = NULL;

    if (usage) init->usage=strdup(usage);
    else       init->usage=NULL;

    return init;
}

void __attribute__((nonnull))
pinit_free (pinit *init) {   
    free (init->classes);

    for (int in_1=0 ; in_1<init->alw_masters_size ; ++in_1) {
        free (init->alw_masters[in_1]);
    }

    free (init->alw_masters);

    if (init->avl_master != NULL) free (init->avl_master->options);
    free (init->avl_master);
    free (init->usage);
    free (init);
}

void __attribute__((nonnull))
pinit_hint(pinit *init) {
    if (init->usage!=NULL) printf ("Usage: %s\n\n", init->usage);

    for (unsigned int in_1=1 ; in_1<init->classes_size ; ++in_1) { /* For Classes */
        printf ("Class: %s\n", init->classes[in_1]->name);
        for (unsigned int in_2=0 ; in_2<init->classes[in_1]->alw_size ; ++in_2) { /* For Options */
            for (unsigned int in_3=0 ; in_3<(init->classes[in_1]->alw_tree[in_2]->names_size) ; ++in_3) { /* For Names of options that have Clone Options */
                if (init->classes[in_1]->alw_tree[in_2]->hint_size!=0) {
                    printf ("  | Opt: %s\n", init->classes[in_1]->alw_tree[in_2]->names[in_3]);
                }
            }
            for (unsigned int in_3=0 ; in_3<(init->classes[in_1]->alw_tree[in_2]->hint_size) ; ++in_3) { 
                printf ("       Hint: %s\n", init->classes[in_1]->alw_tree[in_2]->hints[in_3]);
            }
        }
        
        for (unsigned int in_2=0 ; in_2<init->classes[in_1]->alw_size ; ++in_2) { /* For Names of alone options (Without any clones) */
            for (unsigned int in_3=0 ; in_3<(init->classes[in_1]->alw_tree[in_2]->names_size) ; ++in_3) {
                if (init->classes[in_1]->alw_tree[in_2]->hint_size==0) {
                    printf ("  - Opt: %s\n", init->classes[in_1]->alw_tree[in_2]->names[in_3]);
                }
            }
        }
    }
    
    printf ("\n");
    for (unsigned int in_1=0 ; in_1<init->alw_masters_size ; ++in_1) { /* For Masters */
        if (init->alw_masters[in_1]->hint!=NULL) {
            printf ("Master: %s\n   %s\n", init->alw_masters[in_1]->name, init->alw_masters[in_1]->hint);
        }
        else {
            printf ("Master: %s\n", init->alw_masters[in_1]->name);
        }
    }
}