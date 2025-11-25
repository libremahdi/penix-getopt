#include "pgetopt.h"
#include "../lib/popt_class.h"
#include "../lib/popt_error.h"
#include "salloc.h"

pclass *pclass_create ( pinit **init, char *name )
{    
    (*init)->classes = (struct class **) realloc ( (*init)->classes, ( sizeof (struct class *) * ((*init)->classes_size+1) ) );

    (*init)->classes[(*init)->classes_size]  = salloc (sizeof (struct class));
    (*init)->classes[(*init)->classes_size]->name = name;
    
    (*init)->classes[(*init)->classes_size]->alw_size = 0;
    (*init)->classes[(*init)->classes_size]->avl_size = 0;

    (*init)->classes[(*init)->classes_size]->alw_tree = NULL;
    (*init)->classes[(*init)->classes_size]->avl_tree = NULL;

    return (*init)->classes[(*init)->classes_size++];
}
