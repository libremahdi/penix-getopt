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

static void _printerr_pgetopt (char *err, int _LINE_, char* _FILE_) {
    printf (ANSI_COLOR_RED"Pgetopt Error: "ANSI_COLOR_RESET"File:%s Line:%d\n%s\n", _FILE_, _LINE_, err);
    abort ();
}

static void _printerr_user (char *err, char *opt) {
    printf (ANSI_COLOR_RED"User Error: "ANSI_COLOR_RESET"%s\n%s\n", opt, err);
}

static void _mem_alloc_fail (int _LINE_, char* _FILE_) {
    printf (ANSI_COLOR_RED "Memory Allocation Failure:"ANSI_COLOR_RESET" File:%s Line:%d\n" \
    ANSI_COLOR_YELLOW"hint: Close some heavy software programs that are occupying a lot of memory and try again."ANSI_COLOR_RESET"\n", _FILE_, _LINE_);
}

#endif