#include "pgetopt.h"

void pinit_set_main_class ( pinit **init, pclass *class )
{
    (*init)->classes[0] = class;
}
