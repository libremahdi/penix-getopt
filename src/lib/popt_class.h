/*
 *  Copyright (C) 2025-2026 Mahdi Hosseini Asaad
 *  For more information, please read LICENSE file.
 *
*/

#include <stdbool.h>

#ifndef PGETOPT__POPT_CLASS
#define PGETOPT__POPT_CLASS

#define PGETOPT__FIND_CHAR(STRING, CHAR_P) (int)(strstr(STRING, CHAR_P)-STRING)

/* when you insert the 'class.flag' string, this function must return 'class' from the string
*/ char *pstr_get_class_name (char *);

/* when you insert the 'class.flag' string, this function must return 'flag' from the string.
*/ char *pstr_get_class_value (char *);

bool is_class_syntax_correct (char *);

int get_class_index (pinit *, char *);

/* The hint string is read from palw and assigned to the alw_branch structure. 
 * It allocates the necessary space on its own. It does not return any value.
*/ void internal_add_hint(struct alw_branch *, palw *, unsigned int);

/* if opt_id already exists, this function returns
 * its index in the pclass structure. Otherwise, return the number -1.
*/ int is_alw_tree_repetitive_id (pclass *, unsigned int);

#endif /* PGETOPT__POPT_CLASS */
