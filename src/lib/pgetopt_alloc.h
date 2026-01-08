#include <stddef.h>

#ifndef PGETOPT__SALLOC
#define PGETOPT__SALLOC

void* pgetopt_alloc (size_t size);
void *pgetopt_realloc (void *ptr, size_t size);

#endif /* PGETOPT__SALLOC */
