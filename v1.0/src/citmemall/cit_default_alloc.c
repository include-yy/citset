#include<stdlib.h>

void cit_die(char *);

void *
cit_default_alloc (size_t size)
{
  void * p;

  p = malloc(size);
  if(!p) {
    cit_die("cit_default_alloc: memory exhausted.");
  } else {
    return p;
  }

  return NULL;
}
    
void * (*cit_allocate_func) (size_t) = cit_default_alloc;
