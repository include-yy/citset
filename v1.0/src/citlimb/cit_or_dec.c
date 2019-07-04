#include"cit_def.h"

void
cit_or_dec (cit_unit_ptr fst, cit_unit_ptr sec, size_t start, size_t end, cit_unit_ptr get)
{
  if (start > end) {
    cit_die("cit_or_dec: start index is bigger than end index!");
  } else if (end == CHARUNIT_MAX) {
    cit_die("cit_or_dec: end index is bigger than biggest possible number of unit!");
  } else;

  size_t i;
  if (start == 0) {
    for (i = end; i > 0; i--) {
      get[i] = fst[i] | sec[i];
    }
    get[0] = fst[0] | sec[0];
  } else {
    for (i = end; i >= start; i--) {
      get[i] = fst[i] | sec[i];
    }
  }
    
}
