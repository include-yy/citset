#include"cit_def.h"
#include"cit_limb.h"
#include"citset_in.h"
void
citdFlip (cit_ptr get, cit_ptr var)
{
  EqualCheck(get, var);

  size_t NumOfUnit = var->_cit_size;

  cit_flip_dec(get->_cit_limb, var->_cit_limb, 0, NumOfUnit - 1);

}
    
