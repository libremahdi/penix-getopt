#include "pgetopt.h"
#include "lib/popt_init.h"
#include "lib/popt_class.h"
#include "lib/popt_error.h"
#include "salloc.h"

pinit* pinit_create ()
{
    pinit *init         = (pinit *) salloc (sizeof (pinit));
    init->classes_size  = 1;

    init->classes       = (struct class **) salloc ( ( sizeof (struct class *) ) );
    init->classes[0]    = NULL; // this is the main class

    init->alw_masters_size = 0;
    init->avl_master    = NULL;
    init->alw_masters   = NULL;

    return init;
}






int pinit_get_master_argc ( pinit  *init )
{
    return init->avl_master->options_size;
}

char **pinit_get_master_argv ( pinit  *init )
{
    return init->avl_master->options;
}

char *pinit_get_master_name ( pinit  *init )
{
    if ( init -> avl_master == NULL)
        _printerr_pgetopt ( "The user has not used any Master, but you want to get the name of the available master!", __LINE__, __FILE__ );

    return init->avl_master->name;
}

int pinit_get_master_id ( pinit  *init )
{
    if ( init -> avl_master == NULL)    
    return -1;
    return init->avl_master->master_id;
}


void pinit_free ( pinit **init )
{   
    free ( (*init)->classes );

    for ( int i = 0 ; i < (*init)->alw_masters_size ; ++i )
    {
        free ( (*init)->alw_masters[i] );
    }

    free ( (*init)->alw_masters );

    if ((*init)->avl_master != NULL) free ( (*init)->avl_master->options );
    free ( (*init)->avl_master );
    free ( (*init) );
}
