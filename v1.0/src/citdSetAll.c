#include"cit_def.h"
#include"cit_limb.h"
#include"citset_in.h"

void
citdSetAll (cit_ptr var, int symbol)
{
  cit_zerone_dec(var->_cit_limb, 0, var->_cit_size - 1, symbol);
}
