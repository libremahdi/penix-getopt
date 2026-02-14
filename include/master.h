/*
 *  Copyright (C) Mahdi Hosseini Asaad, All rights reserved.
 *  For more information, please read LICENSE file.
 *
*/

struct master_alw {
    char *name;
    unsigned int master_id;
    char *hint;
};

struct master_avl {
    char *name;
    unsigned int master_id;
    unsigned int options_size;
    char **options;
};
