#include <stdio.h>
#include <string.h>

#include "pgetopt.h"

#ifndef POPT_INIT
#define POPT_INIT

static unsigned int is_avl_tree_repetitive_id ( pclass *class, unsigned int opt_id )
{
    for ( int i = 0 ; i < class->avl_size ; ++i )
        if ( class->avl_tree[i]->opt_id == opt_id ) return i;
    return -1;
}

static int get_id ( pclass *class, char *option )
{
    for ( int classI=0 ; classI < class->alw_size ; ++classI )
    {
        for ( int valueI=0 ; valueI < class->alw_tree[classI]->names_size ; ++valueI )
        {
            if ( strcmp ( class->alw_tree[classI]->names[valueI], option) == 0 )
            {
                return class->alw_tree[classI]->opt_id;
            }
        }
    }
    return -1;
}

static enum PKEY_TYPE get_key_type ( pclass *class, int opt_id )
{
    for ( int i = 0 ; i < class->alw_size ; ++i )
        if ( class->alw_tree[i]->opt_id == opt_id ) return class->alw_tree[i]->key_type;
}

static void _phead_flag ( pinit **init, unsigned int class_index, unsigned int opt_id )
{
    (*init)->classes[class_index]->avl_tree = ( struct avl_branch **) realloc ( ((*init)->classes[class_index]->avl_tree), ( sizeof (struct avl_branch *) * ( (*init)->classes[class_index]->avl_size + 1 )) );
    (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size] = ( struct avl_branch * ) malloc ( sizeof ( struct avl_branch ) );
    (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size]->opt_id        = opt_id;
    (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size]->values_size   = 0;
    (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size]->values        = NULL;
    ++(*init)->classes[class_index]->avl_size;
}

static struct avl_branch **get_avl_point ( pclass *class, unsigned int opt_id )
{
    for ( int i = 0 ; i < class->avl_size ; ++i )
        if ( class->avl_tree[i]->opt_id == opt_id )
            return &class->avl_tree[i];
}

static struct alw_branch **get_alw_point ( pclass *class, unsigned int opt_id )
{
    for ( int i = 0 ; i < class->alw_size ; ++i )
        if ( class->alw_tree[i]->opt_id == opt_id )
            return &class->alw_tree[i];
}

static bool is_value_allowed ( struct alw_branch *alw_tree, char *value )
{
    for ( int i = 0 ; i < alw_tree->values_size ; ++i )
    {
        if ( strcmp (alw_tree->values[i], value ) == 0 )
            return true;
    }
    return false;
}



static int _phead_key ( pinit **init, unsigned int class_index, unsigned int opt_id, char *value )
{
    struct alw_branch **alw_key_point = get_alw_point ( (*init)->classes[class_index], opt_id );

    if ( ((*alw_key_point)->key_type == ALW_CUSTOM) && (is_value_allowed ( (*alw_key_point), value ) == 0) )
        return -1;
    if ( ((*alw_key_point)->key_type == DENY_CUSTOM) && (is_value_allowed ( (*alw_key_point), value ) == 1) )
        return -1;

    (*init)->classes[class_index]->avl_tree = ( struct avl_branch **) realloc ( ((*init)->classes[class_index]->avl_tree), ( sizeof (struct avl_branch *) * ( (*init)->classes[class_index]->avl_size + 1 )) );
    (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size] = ( struct avl_branch * ) malloc ( sizeof ( struct avl_branch ) );
    (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size]->opt_id        = opt_id;
    (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size]->values_size   = 1;
    (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size]->values        = ( char ** ) malloc ( sizeof (char *) );
    (*init)->classes[class_index]->avl_tree[(*init)->classes[class_index]->avl_size]->values[0]     = value;
    ++(*init)->classes[class_index]->avl_size;
}


static int _phead_repetitive_key ( pinit **init, unsigned int class_index, unsigned int opt_id, char *value )
{
    struct avl_branch **key_point = get_avl_point ((*init)->classes[class_index], opt_id);
    struct alw_branch **alw_key_point = get_alw_point ( (*init)->classes[class_index], opt_id );

    if ( ((*alw_key_point)->key_type == ALW_CUSTOM) && (is_value_allowed ( (*alw_key_point), value ) == 0) )
        return -1;
    if ( ((*alw_key_point)->key_type == DENY_CUSTOM) && (is_value_allowed ( (*alw_key_point), value ) == 1) )
        return -1;   

    (*key_point)->values   = ( char ** ) realloc ( (*key_point)->values, (sizeof (char *) * ((*key_point)->values_size+1)));
    (*key_point)->values [(*key_point) -> values_size] = value;
    ++(*key_point) -> values_size;
}
#endif