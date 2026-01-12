/*
 *  Copyright (C) Parabyte Company, All rights reserved.
 *  For more information, please read LICENSE file.
 *
*/

#include <stddef.h>

#ifndef PGETOPT__SALLOC
#define PGETOPT__SALLOC

void* pgetopt__alloc (size_t size);
void *pgetopt__realloc (void *ptr, size_t size);

#endif /* PGETOPT__SALLOC */
