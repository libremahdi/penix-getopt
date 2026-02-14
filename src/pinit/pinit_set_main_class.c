/*
 *  Copyright (C) Mahdi Hosseini Asaad, All rights reserved.
 *  For more information, please read LICENSE file.
 *
*/

#include "pgetopt.h"
#include "branch.h"

void __attribute__((nonnull))
pinit_set_main_class (pinit *init, pclass *class) {
    init->classes[0] = class;
}
