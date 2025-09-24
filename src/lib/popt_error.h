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


#endif