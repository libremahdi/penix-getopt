/*++
 *  PARABYTE PENIX PGETOPT (PLIBC)
 *  
 *  Copyright (C) 2025-2026 Parabyte Company, All rights reserved.
 *  FILE: pclass_key.c
 *
 *  For more information, please read LICENSE file.
 *--
*/

#include <stdio.h>

#include "pgetopt.h"
#include "../lib/popt_error.h"
#include "branch.h"
#include "pgetopt_alloc.h"

unsigned int pclass_get_key_size (pclass *class, unsigned int opt_id) {
    for (int classI=0 ; classI < (class)->avl_size ; ++classI) {
        if ((class)->avl_tree[classI]->opt_id == opt_id) {
            return (class)->avl_tree[classI]->values_size;
        }
    }
    char *err; sprintf (err, "No available key found under this opt_id: %d", opt_id); 
    /* The user may not have used any key, but you want to get the number of values of that key!
    */
    pgetopt__printerr (err, __LINE__, __FILE__);
}

char *pclass_key_loop_get_value (pclass  *class, unsigned int opt_id, unsigned int index) {
    for (int classI=0 ; classI <  (class)->avl_size ; ++classI) {
        if ((class)->avl_tree[classI]->opt_id == opt_id) {
            return (class)->avl_tree[classI]->values[index];
        }
    }
    char *err; sprintf (err, "No available key found under this opt_id: %d", opt_id); 
    /* The user may not have used any key, but you want to get the values of that key!
    */
    pgetopt__printerr (err, __LINE__, __FILE__);
}

pkey *pclass_set_key (pclass *class, unsigned int opt_id, enum PKEY_TYPE key_type) {
    for (int classI = 0 ; classI < class->alw_size ; ++classI) {
        if (class->alw_tree[classI]->opt_id == opt_id) {
            class->alw_tree[classI]->key_type = key_type;
            return class->alw_tree[classI];
        }
    }
    char *err; sprintf (err, "No opt_id with number %d was found to convert it to kay", opt_id); 
    /* This error is issued when you want to set an option to key but such an opt_id is not found.
    */
    pgetopt__printerr (err, __LINE__, __FILE__);
}

void pkey_set_custom_value (pkey *key, char *value) {
    key->values = pgetopt__realloc (key->values, (sizeof (char *)*(key->values_size+1)));
    key->values[(key->values_size)] = value;
    ++key->values_size;
}
