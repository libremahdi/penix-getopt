#ifndef POPT_ERROR
#define POPT_ERROR

#define _without_error 0
#define _invalid_option  1
#define _key_without_value 2
#define _lack_of_class 3
#define _class_syntax_error 4
#define _invalid_value 5
#define _lack_of_master 6


static void _printerr_pgetopt ( char *err, int _LINE_, char* _FILE_ )
{
    printf ( "Pgetopt Error: File:%s Line:%d\n%s\n", _FILE_, _LINE_, err );
    abort ();
}

static void _printerr_user ( char *err, char *opt )
{
    printf ("Error: %s\n%s\n", opt, err);
}

static void _mem_alloc_fail ( int _LINE_, char* _FILE_) {
    printf ("Memory Allocation Failure: File:%s Line:%d\npgetopt could not reserve memory. \
    The problem might be due to the RAM being full, or due to a bug or error in the operating \
    system.\nhint: Close some heavy software programs that are occupying a lot of memory and try again.\n", _FILE_, _LINE_);
}

#endif