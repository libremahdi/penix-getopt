/*
 *  Copyright (C) 2025-2026 Mahdi Hosseini Asaad
 *  For more information, please read LICENSE file.
 *
*/

#include "pgetopt.h"
#include "branch.h"

int __attribute__((nonnull))
pclass_loop_get_opt_id (pclass *class, unsigned int index) {
    if (index >= (class->avl_size))    return -1;
    return class->avl_tree[index]->opt_id;
}
