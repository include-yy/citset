#ifndef _CIT_HELPER_
  #define _CIT_HELPER_

#include<stddef.h>

extern void * (*cit_allocate_func) (size_t total);
extern void * (*cit_reallocate_func) (void* p, size_t old, size_t new);
extern void (*cit_free_func) (void * p, size_t total);

#define cit_alloc(size) ((*cit_allocate_func)((size)))
#define cit_free(p) ((*cit_free_func) ((p), 0))

#endif
