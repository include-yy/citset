#include"cit_def.h"

void
cit_flip_inc (cit_unit_ptr d, cit_unit_ptr s, size_t start, size_t end)
{
  if (start > end) {
    cit_die("cit_flip_inc: start index is bigger than end index!");
  } else if (end == CHARUNIT_MAX) {
    cit_die("cit_flip_inc: end index is bigger than biggest possible number of unit!");
  } else;

  size_t i;
  for (i = start; i <= end; i++) {
    d[i] = ~ s[i];
  }

}
