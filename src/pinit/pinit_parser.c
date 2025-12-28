#include "pgetopt.h"
#include "../lib/popt_init.h"
#include "../lib/popt_class.h"
#include "../lib/popt_error.h"
#include "branch.h"
#include "master.h"
#include "pgetopt_alloc.h"

usrerr pinit_parser (pinit *init, int argc, char **argv) {
    int opt_id;

    union _INDEX { int class_id; int master_id; } glob_index;

    for (int i = 1 ; i < argc ; ++i) {
        if ((strlen (argv[i]) == 2) && (argv[i][0] == '-') && (argv[i][1] != '-')) { // it's either a single short flag or a key
            if ((opt_id = get_opt_id (init->classes[0], argv[i]+1)) == -1) // When an undefined option is used by the user.
                /* When the user has used an option as a software parameter that has not been defined by the software developer, 
                 * get_opt_id returns the value -1 and this condition is executed.
                */
                return _setup_return_usrerr (_invalid_option, i, __LINE__, __FILE__);

            switch (get_key_type (init->classes[0], opt_id)) {
                case VOID:
                    if (is_avl_tree_repetitive_id (init->classes[0], opt_id) == -1) // -1 means no
                        _phead_flag (&init, 0, opt_id);
                    break;
                default:
                    if ((i+1 >= argc) || (!IsValueReallyAValue (argv[i+1]))) 
                        /* Values cannot start with - or @
                         * Also if the key is the last option at the end of the options and the user has not defined
                         * any value after it. ex: command --key 
                         * where is the value after --key?? i dont know (lol)!
                        */ return _setup_return_usrerr (_key_without_value, i, __LINE__, __FILE__);

                    if (is_avl_tree_repetitive_id (init->classes[0], opt_id) == -1) { // -1 means no
                        if (_phead_key (&init, 0, opt_id, argv[i+1]) == -1)
                            /* When the user uses a value that is not defined by the programmer
                            */ return _setup_return_usrerr (_invalid_value, i, __LINE__, __FILE__);
                        ++i;
                        continue;
                    }
                    if (_phead_repetitive_key (&init, 0, opt_id, argv[i+1]) == -1)
                            return _setup_return_usrerr (_invalid_option, i, __LINE__, __FILE__);
                    ++i;
                    break;
            }
        }
        else if ((argv[i][0] == '-') && (argv[i][1] != '-')) { // They must be flag
            for (int j = 1 ; j <= strlen (argv[i])-1 ; ++j) {
                char *char2strv = (char *) pgetopt_alloc (sizeof (char) * 2);
                char2strv[0] = argv[i][j]; 
                char2strv[1]='\0';
                
                if ((opt_id = get_opt_id (init->classes[0], char2strv)) == -1) {
                    free (char2strv);
                    return _setup_return_usrerr (_invalid_option, i, __LINE__, __FILE__);
                }
                if ((*get_alw_point (init->classes[0], opt_id))->key_type != VOID) { // if M is a key and F is a flag, they cannot be written in compressed (-MF or -FM)
                    free (char2strv);
                    return _setup_return_usrerr (_key_without_value, i, __LINE__, __FILE__);
                }

                if (is_avl_tree_repetitive_id (init->classes[0], opt_id) == -1) // -1 means no
                    _phead_flag (&init, 0, opt_id);

            }

        }
        else if (argv[i][0] == '-' && argv[i][1] == '-') { // long options
            if ((opt_id = get_opt_id (init->classes[0], argv[i] + 2)) == -1)
                return _setup_return_usrerr (_invalid_option, i, __LINE__, __FILE__);

            switch (get_key_type (init->classes[0], opt_id)) {
                case VOID:
                    if (is_avl_tree_repetitive_id (init->classes[0], opt_id) == -1) // -1 means no
                        _phead_flag (&init, 0, opt_id);
                    break;
                default:
                    if ((i+1 >= argc) || (!IsValueReallyAValue (argv[i+1])))
                        /* Values cannot start with - or @
                         * Also if the key is the last option at the end of the options and the user has not defined
                         * any value after it. ex: command --key 
                         * where is the value after --key?? i dont know (lol)!
                        */ return _setup_return_usrerr (_key_without_value, i, __LINE__, __FILE__);

                    if (is_avl_tree_repetitive_id (init->classes[0], opt_id) == -1) { // -1 means no
                        if (_phead_key (&init, 0, opt_id, argv[i+1]) == -1)
                            /* When the user uses a value that is not defined by the programmer
                            */ return _setup_return_usrerr (_invalid_value, i, __LINE__, __FILE__);
                        ++i;
                        continue;
                    }
                    if (_phead_repetitive_key (&init, 0, opt_id, argv[i+1]) == -1)
                        /* When the user uses a value that is not defined by the programmer
                        */ return _setup_return_usrerr (_invalid_value, i, __LINE__, __FILE__);
                    ++i;
                    break;
            }
        }
        else if (argv[i][0] == '@') { // Must be a class
            char *class_name = NULL;
            char *class_value = NULL;

            char *char2strv = strdup (argv[i]+1);
            if (!is_class_syntax_correct (char2strv)) {
                free (char2strv);
                return _setup_return_usrerr (_class_syntax_error, i, __LINE__, __FILE__);
            }
            class_name  = pstr_get_class_name (char2strv);
            class_value = pstr_get_class_value (char2strv);
            free (char2strv);

            if ((glob_index.class_id = get_class_index (init, class_name)) == -1)  {
                free (class_name);
                free (class_value);
                return _setup_return_usrerr (_lack_of_class, i, __LINE__, __FILE__);
            }
            free (class_name);
            
            if ((opt_id = get_opt_id (init->classes[glob_index.class_id], class_value)) == -1)
                return _setup_return_usrerr (_invalid_option, i, __LINE__, __FILE__);
            free (class_value);

            switch (get_key_type (init->classes[glob_index.class_id], opt_id)) {
                case VOID:
                    if (is_avl_tree_repetitive_id (init->classes[glob_index.class_id], opt_id) == -1) // -1 means no
                        _phead_flag (&init, glob_index.class_id, opt_id);
                    break;
                default:
                    if ((i+1 >= argc) || (!IsValueReallyAValue (argv[i+1])))
                        /* Values cannot start with - or @
                         * Also if the key is the last option at the end of the options and the user has not defined
                         * any value after it. ex: command --key 
                         * where is the value after --key?? i dont know (lol)!
                        */ return _setup_return_usrerr (_key_without_value, i, __LINE__, __FILE__);

                    if (is_avl_tree_repetitive_id (init->classes[glob_index.class_id], opt_id) == -1) { // -1 means no
                        if (_phead_key (&init, glob_index.class_id, opt_id, argv[i+1]) == -1)
                            /* When the user uses a value that is not defined by the programmer
                            */ return _setup_return_usrerr (_invalid_value, i, __LINE__, __FILE__);
                        ++i;
                        continue;
                    }
                    if (_phead_repetitive_key (&init, glob_index.class_id, opt_id, argv[i+1]) == -1)
                    /* When the user uses a value that is not defined by the programmer
                    */ return _setup_return_usrerr (_invalid_value, i, __LINE__, __FILE__);
                    ++i;
                    break;
            }
        }
        else {
            if ((glob_index.master_id = get_master_id (init, argv[i])) == -1) 
                /* When the user uses a master that is not defined!
                */ return _setup_return_usrerr (_lack_of_master, i, __LINE__, __FILE__); 
    
            init->avl_master = pgetopt_alloc (sizeof (struct master_avl));
            init->avl_master->name = argv[i];
            init->avl_master->master_id = glob_index.master_id;
            init->avl_master->options_size = argc - i;
            init->avl_master->options = get_master_options (argc, argv, i);
            break;
        }
        
    }
    /* Because the pinit_parser function must always return a value, no error is issued in this method.
    */ _setup_return_usrerr (_without_error, -1, __LINE__, __FILE__);
}