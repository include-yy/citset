#include<stdlib.h>

void cit_die(char *);

void *
cit_default_realloc (void * old, size_t old_size, size_t new_size)
{
  void * p = NULL;

  p = realloc(old, new_size);
  if(!p) {
    cit_die("cit_default_realloc: memory exausted.");
  } else {
    return p;
  }
  
  return NULL;
}
    
void * (*cit_reallocate_func) (void *, size_t, size_t) = cit_default_realloc;
