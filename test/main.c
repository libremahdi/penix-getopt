#include "pgetopt.h"
#include "t-lib/opts.h"

#include <stdio.h>

int main (int argc, char **argv) {
    pinit *init = pinit_create ("This is a simple Usage text\nyou can use new_line character...");

    pclass *main = pclass_create (init, "main");
    pinit_set_main_class (init, main);
    palw main_allowed_options [] = {
		{ 1, "f"   , "This is short option."},
		{ 1, "flag", "This is clone long option." },

		{ 2, "k"   , "This is short key."},
		{ 2, "key" , "This is clone long Key!"},

        { 3, "opt_3" } , /* No Hint */
        EOL
    };
    pclass_set_allowed_options (main, main_allowed_options);

    pkey *pkey_2=pclass_set_key (main, 2, ALW_CUSTOM);
    pkey_set_custom_value (pkey_2, "value-1");
    pkey_set_custom_value (pkey_2, "value-2");
    
    pclass *user = pclass_create (init, "user");
    palw user_allowed_options [] = {
		{ 1, "name" , "User's Name" },
		{ 2, "email", "User's Email"},
        EOL
    };
    pclass_set_allowed_options (user, user_allowed_options);
    pclass_set_key (user, 1, NONE);
    pclass_set_key (user, 2, NONE);


    palw master_avl [] = {
        { 1 , "master_1"    , "This is Master_1" },
        { 1 , "c_master_1"  , "This is Clone of the Master_1" }, // clone master
        { 2 , "master_2"  } , // No Hint
        EOL
    };
    pinit_set_allowed_masters (init, master_avl);

    usrerr _error = pinit_parser (init, argc, argv);
    if (usererror_parser (_error, argv)) goto EXIT;

    char **_argv;
    switch (pinit_get_master_id (init)) {
        case 1:
            if (
                master_1(
                /* argc= */ pinit_get_master_argc (init),
                /* argv= */ pinit_get_master_argv (init)
                )) goto EXIT;
            break;
        case 2:
            if (
                master_2(
                /* argc= */ pinit_get_master_argc (init),
                /* argv= */ pinit_get_master_argv (init)
                )) goto EXIT;
            break;
    }
    {
        int opt_id, i;
        i=0;
        while ((opt_id = pclass_loop_get_opt_id (main, i)) != -1) {
            switch (opt_id) {
                case (1):
                    printf ("long_flag\n");
                    break;
                case (2):
                    for (int vi=0 ; vi < pclass_get_key_size (main, 2) ; ++vi) {
                        printf ("key = %s\n", pclass_key_loop_get_value (main, 2, vi));
                    }
                    break;

            }
            ++i;
        }

        i=0;
        while ((opt_id = pclass_loop_get_opt_id (user, i)) != -1) {
            switch (opt_id) {
                case (1):
                    for (int vi=0 ; vi < pclass_get_key_size (user, 1) ; ++vi) {
                        printf ("name = %s\n", pclass_key_loop_get_value (user, 1, vi));
                    }
                    break;
                case (2):
                    for (int vi=0 ; vi < pclass_get_key_size (user, 2) ; ++vi)
                    {
                        printf ("ID = %s\n", pclass_key_loop_get_value (user, 2, vi));
                    }
                    break;
            }
            ++i;
        }
    }
EXIT:
    pclass_free (user);
    pclass_free (main);
    pinit_free  (init);
    return 0;
}