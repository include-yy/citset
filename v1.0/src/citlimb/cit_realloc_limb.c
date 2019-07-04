#include"cit_memall.h"
#include"cit_def.h"

cit_unit_ptr
cit_realloc_limb (cit_unit_ptr old, size_t size)
{
  return (cit_unit_ptr)(*cit_reallocate_func)(old, 0, size * sizeof(cit_unit));
}
