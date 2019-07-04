#include"cit_memall.h"
#include"cit_def.h"

cit_unit_ptr
cit_alloc_limb (size_t size)
{
  return (cit_unit_ptr)cit_alloc(size * sizeof(cit_unit));
}
