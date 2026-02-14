/* 
 * Copyright (C) 2025-2026 Mahdi Hosseini Asaad
 * For more information, please read LICENSE file.
 */

#include "pgetopt.h"
#include <stdio.h>

int master_2(int argc, char **argv) {
    pinit *cr_init = pinit_create ("This is a simple Usage for master_2 Master");

    pclass *cr_main = pclass_create (cr_init, "main");
    pinit_set_main_class (cr_init, cr_main);
    palw main_allowed_options [] = {
        { 1, "opt_1", "This is opt_1" },
        EOL
    };
    pclass_set_allowed_options (cr_main, main_allowed_options);

    palw cr_master_avl [] = {
        { 1 , "sub_master_2", "Sub Master for master_2"},
        EOL
    };
    pinit_set_allowed_masters (cr_init, cr_master_avl);

    usrerr cr_error = pinit_parser (cr_init, argc, argv);
    if (usererror_parser (cr_error, argv)) {
        printf("ERROR\n");
        pclass_free (cr_main);
        pinit_free (cr_init);
        return 1;
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
                printf ("master_2: opt_1\n");
                break;
        }
        ++i;
    }

    pclass_free (cr_main);
    pinit_free (cr_init);

    return 0;
}