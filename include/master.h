/*
 *  Copyright (C) 2025-2026 Mahdi Hosseini Asaad
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
