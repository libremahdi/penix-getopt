#include <stdbool.h>

#ifndef PGETOPT__POPT_CLASS
#define PGETOPT__POPT_CLASS

#define ___FIND_CHAR_INDEX___(STRING, CHAR_P) (strstr(STRING, CHAR_P)-STRING)

/* if opt_id already exists, this function returns
 * its index in the pclass structure. Otherwise, return the number -1.
*/ int is_alw_tree_repetitive_id ( pclass *, unsigned int );

/* when you insert the 'class.flag' string, this function must return 'class' from the string
*/ char *pstr_get_class_name (char *);

/* when you insert the 'class.flag' string, this function must return 'flag' from the string.
*/ char *pstr_get_class_value (char *str);

bool is_class_syntax_correct (char *str);

int get_class_index (pinit *init, char *class_name);

#endif /* PGETOPT__POPT_CLASS */
