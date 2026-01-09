#include <string.h>

#include "pgetopt.h"
#include "popt_class.h"
#include "branch.h"
#include "pgetopt_alloc.h"
#include <stdbool.h>

int is_alw_tree_repetitive_id (pclass *class, unsigned int opt_id) {
    for (int i = 0 ; i < class->alw_size ; ++i)
        if (class->alw_tree[i]->opt_id == opt_id) return i;
    return -1;
}

char *pstr_get_class_name (char *str) {
    const unsigned int find_dot_char = PGETOPT__FIND_CHAR(str, ".");

    char *ret_value = pgetopt__alloc (sizeof (char) * find_dot_char+1); // one character for \0
    strncpy (ret_value, str, find_dot_char);
    ret_value [find_dot_char]='\0';
    return ret_value;
}

char *pstr_get_class_value (char *str) {
    char *ret_value = strdup (str + PGETOPT__FIND_CHAR(str, ".")+1);
    return ret_value;
}

bool is_class_syntax_correct (char *str) {
    unsigned int strln = strlen (str);
    for (unsigned int i = 0 ; i < strln ; ++i)
    {
        if (str[i] == '.')    return true;
    }
    return false;
}

int get_class_index (pinit *init, char *class_name) {
    for (unsigned int i = 0 ; i < init->classes_size ; ++i)
    {
        if (strcmp (init->classes[i]->name, class_name) == 0)
            return i;
    }
    return -1;
}
