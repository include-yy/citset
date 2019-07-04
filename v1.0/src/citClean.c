#include"cit_def.h"
#include"cit_limb.h"
#include"citset_in.h"

void
citClean (cit_ptr var)
{
  cit_free_limb(var->_cit_limb);

  var->_cit_alloc = 0;
  var->_cit_size = 0;
  var->_cit_limb = NULL;
  
}
