/*
 *  Copyright (C) Parabyte Company, All rights reserved.
 *  For more information, please read LICENSE file.
 *
*/

#include "pgetopt.h"
#include "branch.h"

void pinit_set_main_class (pinit *init, pclass *class) {
    init->classes[0] = class;
}
