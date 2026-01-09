/*++
 *  PARABYTE PENIX PGETOPT (PLIBC)
 *  
 *  Copyright (C) 2025-2026 Parabyte Company, All rights reserved.
 *  FILE: pinit_set_main_class.c
 *
 *  For more information, please read LICENSE file.
 *--
*/

#include "pgetopt.h"
#include "branch.h"

void pinit_set_main_class (pinit *init, pclass *class) {
    init->classes[0] = class;
}
