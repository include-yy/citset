#include"cit_def.h"
#include"cit_limb.h"
#include"citset_in.h"

void
citdCopy (cit_ptr get, cit_ptr var)
{
  EqualCheck(get, var);

  size_t NumOfUnit = var->_cit_size;
  cit_unit_ptr fst = get->_cit_limb;
  cit_unit_ptr sec = var->_cit_limb;

  cit_copy_dec(fst, sec, 0, NumOfUnit - 1);

}
  
