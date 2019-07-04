#include"cit_def.h"

void
cit_xor_inc (cit_unit_ptr fst, cit_unit_ptr sec, size_t start, size_t end, cit_unit_ptr get)
{
  if (start > end) {
    cit_die("cit_xor_inc: start index is bigger than end index!");
  } else if (end == CHARUNIT_MAX) {
    cit_die("cit_xor_inc: end index is bigger than biggest possible number of unit!");
  } else;
    
  
  size_t i;
  for(i = start; i <= end; i++) {
    get[i] = fst[i] ^ sec[i];
  }

}
