/*++
 *  PARABYTE PENIX PGETOPT (PLIBC)
 *  
 *  Copyright (C) 2025-2026 Parabyte Company, All rights reserved.
 *  FILE: pclass_loop_get_opt_id.c
 *
 *  For more information, please read LICENSE file.
 *--
*/

#include "pgetopt.h"
#include "branch.h"

int pclass_loop_get_opt_id (pclass  *class, unsigned int index) {
    if (index >= (class->avl_size))    return -1;
    return class->avl_tree[index]->opt_id;
}
