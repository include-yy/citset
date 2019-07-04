#include"cit_def.h"
#include"cit_limb.h"
#include"citset_in.h"

void
citdLogic (cit_ptr get, cit_ptr foo, cit_ptr bar, int signal)
{
  EqualCheck(get, foo);
  EqualCheck(get, bar);
 
  size_t NumOfUnit = foo->_cit_size;
  cit_unit_ptr now = get->_cit_limb;
  cit_unit_ptr fst = foo->_cit_limb;
  cit_unit_ptr sec = bar->_cit_limb;
  
  if (signal == AND) {
    cit_and_dec(fst, sec, 0, NumOfUnit, now);
  } else if (signal == OR) {
    cit_or_dec(fst, sec, 0, NumOfUnit, now);
  } else if (signal == XOR) {
    cit_xor_dec(fst, sec, 0, NumOfUnit, now);
  } else {
    cit_die("citdLogic: signal error, which must be AND, OR, or XOR!");
  }

}
  
