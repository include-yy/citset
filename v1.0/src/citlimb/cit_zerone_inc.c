#include"cit_def.h"

void
cit_zerone_inc (cit_unit_ptr p, size_t start, size_t end, int signal)
{
  if (start > end) {
    cit_die("cit_zerone_inc: start index is bigger than end index!");
  } else if (end == CHARUNIT_MAX) {
    cit_die("cit_zerone_inc: end index is bigger than the biggest possible number of unit!");
  } else;

  size_t i;
  if (signal == ONE) {
    for (i = start; i <= end; i++) {
      p[i] = -1;
    }
  } else if (signal == ZERO) {
    for (i = start; i <= end; i++) {
      p[i] = 0;
    }
  } else {
    cit_die("cit_zerone_inc: signal error, which must be ONE or ZERO!");
  }

}
