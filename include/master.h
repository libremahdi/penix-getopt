/*++
 *  PARABYTE PENIX PGETOPT (PLIBC)
 *  
 *  Copyright (C) 2025-2026 Parabyte Company, All rights reserved.
 *  FILE: master.h
 *
 *  For more information, please read LICENSE file.
 *--
*/

struct master_alw {
    char *name;
    unsigned int master_id;
};

struct master_avl {
    char *name;
    unsigned int master_id;
    unsigned int options_size;
    char **options;
};
