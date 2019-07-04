#include"cit_def.h"

void
cit_copy_dec (cit_unit_ptr d, cit_unit_ptr s, size_t start, size_t end)
{
  if (start > end) {
    cit_die("cit_copy_dec: start index is bigger than end index!");
  } else if (end == CHARUNIT_MAX) {
    cit_die("cit_copy_dec: end index is bigger than biggest possible number of unit!");
  } else;
    
  size_t i;
  if (start == 0) {
    for (i = end; i > 0; i--) {
      d[i] = s[i];
    }
    d[0] = s[0];
  } else {
    for (i = end; i >= start; i--) {
      d[i] = s[i];
    }
  }

}
