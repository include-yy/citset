#include<stdlib.h>

void
cit_default_free (void * p, size_t size)
{
  free(p);
}

void (*cit_free_func) (void*, size_t) = cit_default_free;

