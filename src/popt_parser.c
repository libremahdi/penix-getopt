#ifndef POPT_PARSER
#define POPT_PARSER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lib/popt_string.h"
#include "pgetopt.h"

char ploop_get_flags ( popt *root, unsigned long int i )
{
    if ( i >= (root->flags_num) )
        return EOO;
    if (root->tree[i]->branches == NULL)
        return root->tree[i]->name[0];

}

#endif