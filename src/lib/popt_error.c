/*
 *  Copyright (C) 2025-2026 Mahdi Hosseini Asaad
 *  For more information, please read LICENSE file.
 *
*/

#include "popt_error.h"
#include <stdlib.h>
#include <stdio.h>

void pgetopt__printerr (char *err, int _LINE_, char* _FILE_) {
    printf (ANSI_COLOR_RED"Pgetopt Error: "ANSI_COLOR_RESET"File:%s Line:%d\n%s\n", _FILE_, _LINE_, err);
    abort ();
}

void pgetopt__printerr_user (char *err, char *opt) {
    printf (ANSI_COLOR_RED"User Error: "ANSI_COLOR_RESET"%s\n%s\n", opt, err);
}

void pgetopt__mem_alloc_fail (int _LINE_, char* _FILE_) {
    printf (ANSI_COLOR_RED "Memory Allocation Failure:"ANSI_COLOR_RESET" File:%s Line:%d\n" \
    ANSI_COLOR_YELLOW"hint: Close some heavy software programs that are occupying a lot of memory and try again."ANSI_COLOR_RESET"\n", _FILE_, _LINE_);
}
