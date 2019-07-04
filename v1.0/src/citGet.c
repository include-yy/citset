#include"cit_def.h"
#include"cit_limb.h"
#include"citset_in.h"

extern size_t cit_place[2];

size_t
citGet (cit_ptr var, bit_index index)
{
  IndexCheck(var, index);
  cit_tell(index);

  cit_unit_ptr operand = var->_cit_limb;
  operand += cit_place[0];

  return cit_unit_get(operand, cit_place[1]);
}
