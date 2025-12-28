#ifndef POPT_ERROR
#define POPT_ERROR

#define _without_error 0
#define _invalid_option  1
#define _key_without_value 2
#define _lack_of_class 3
#define _class_syntax_error 4
#define _invalid_value 5
#define _lack_of_master 6

#define ANSI_COLOR_RED     "\x1b[31m"
// #define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
// #define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void _printerr_pgetopt  (char *, int, char*);
void _printerr_user     (char *, char *);
void _mem_alloc_fail    (int, char* );

#endif