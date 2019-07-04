#include"cit_def.h"

size_t
cit_unit_get (cit_unit_ptr p, size_t index)
{
  return ((*p << index) & CIT_UNIT_MSB) >> (UNITBITS - 1);
}
