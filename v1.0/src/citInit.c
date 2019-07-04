#include"cit_def.h"
#include"cit_limb.h"
#include"citset_in.h"

void
citInit (cit_ptr var, bit_index total, int symbol)
{
  if (total == 0) {
    cit_die("citInit: total is zero!");
  } else;

  size_t NumOfUnit = (total - 1) / UNITBITS + 1;

  var->_cit_alloc = total;
  var->_cit_size = NumOfUnit;
  var->_cit_limb = cit_alloc_limb(NumOfUnit);

  cit_zerone_dec(var->_cit_limb, 0, NumOfUnit - 1, symbol);

}
  
    

