/*
 *  Copyright (C) Parabyte Company, All rights reserved.
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
*/ char *pstr_get_class_value (char *str);

bool is_class_syntax_correct (char *str);

int get_class_index (pinit *init, char *class_name);

#endif /* PGETOPT__POPT_CLASS */
