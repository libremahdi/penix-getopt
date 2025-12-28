#include "pgetopt.h"
#include "branch.h"

void pinit_set_main_class (pinit *init, pclass *class) {
    init->classes[0] = class;
}
