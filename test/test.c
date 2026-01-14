#include "pgetopt.h"
#include <stdio.h>

int main (int argc, char **argv) {
    pinit *init = pinit_create ("This is simple Usage Hint!\nThis is another Line!!\nThis is too...");

    pclass *main = pclass_create (init, "main");
    pinit_set_main_class (init, main);
    palw main_allowed_options [] = {
		{ 1, "opt_1", "Hint 1"},
		{ 1, "c_opt_1", "Continue the Hint 1"},
		{ 2, "opt_2", "Hint 2"},
        { 3, "opt_3"}, /* No Hint */
        EOL
    };
    pclass_set_allowed_options (main, main_allowed_options);

    pkey *a=pclass_set_key (main, 2, ALW_CUSTOM);
    pkey_set_custom_value (a, "value 1");
    
    pclass *user = pclass_create (init, "user");
    palw user_allowed_options [] = {
		{ 1, "opt_1", "Hint 1" },
		{ 2, "opt_2", "Hint 2"},
        EOL
    };
    pclass_set_allowed_options (user, user_allowed_options);
    pclass_set_key (user, 1, NONE);
    pclass_set_key (user, 2, NONE);


    palw master_avl [] = {
        { 1 , "master_1", "Hint 1" },
        { 1 , "c_master_1", "Hint 2" }, // clone master
        { 2 , "master_2" }, // No Hint
        EOL
    };
    pinit_set_allowed_masters (init, master_avl);

    usrerr _error = pinit_parser (init, argc, argv);
    if (usererror_parser (_error, argv)) goto EXIT;

    char **_argv;
    switch (pinit_get_master_id (init)) {
        case 1:
            // Create Class
            pinit *cr_init = pinit_create (NULL);

            pclass *cr_main = pclass_create (cr_init, "main");
            pinit_set_main_class (cr_init, cr_main);
            palw main_allowed_options [] = {
                { 1, "opt_1" },
                EOL
            };
            pclass_set_allowed_options (cr_main, main_allowed_options);

            palw cr_master_avl [] = {
                { 1 , "sub_master_1" },
                EOL
            };
            pinit_set_allowed_masters (cr_init, cr_master_avl);

            char **_argv = pinit_get_master_argv (init);
            int _argc = pinit_get_master_argc (init);

            usrerr cr_error = pinit_parser (cr_init, _argc, _argv);
            if (usererror_parser (cr_error, _argv)) {
                printf("ERROR\n");
                pclass_free (cr_main);
                pinit_free (cr_init);
                goto EXIT;
            }

            char **cr_argv;
            switch (pinit_get_master_id (cr_init)) {
                case 1:
                    printf ("Sub Master 1\n");
                    break;
            }

            int i=0, opt_id;
            while ((opt_id = pclass_loop_get_opt_id (cr_main, i)) != -1) {
                switch (opt_id) {
                    case (1):
                        printf ("master_1: opt_1\n");
                        break;
                }
                ++i;
            }

            pclass_free (cr_main);
            pinit_free (cr_init);
            break;
        case 2:
            printf ("Sub Master 3\n");
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

/* $ ./output/test --opt_1 --c_opt_1 --opt_2 "value 1" --opt_3 @user.opt_1 "Any Value" @user.opt_2 Any_Value master_1 --opt_1 sub_master_1                   
    Sub Master 1
    master_1: opt_1
    long_flag
    key = value 1
    name = Any Value
    ID = Any_Value

   $ ./output/test --help
    Usage: This is simple Usage Hint!
    This is another Line!!
    This is too...

    Class: main
    + Opt: opt_1
    + Opt: c_opt_1
        Hint: Hint 1
        Hint: Continue the Hint 1
    + Opt: opt_2
        Hint: Hint 2
    - Opt: opt_3
    Class: user
    + Opt: opt_1
        Hint: Hint 1
    + Opt: opt_2
        Hint: Hint 2

    Master: master_1
    Hint 1
    Master: c_master_1
    Hint 2
    Master: master_2
*/
