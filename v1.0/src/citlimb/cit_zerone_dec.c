#include"cit_def.h"

void
cit_zerone_dec (cit_unit_ptr p, size_t start, size_t end, int signal)
{
  if (start > end) {
    cit_die("cit_zerone_dec: start index is bigger than end index!");
  } else if (end == CHARUNIT_MAX) {
    cit_die("cit_zerone_dec: end index is bigger the biggest possible number of unit!");
  } else;

  size_t i;
  if (signal == ONE) {
    if (start == 0) {
      for (i = end; i > 0; i--) {
	p[i] = -1;
      }
      p[0] = -1;
    } else {
      for (i = end; i >= start; i--) {
	p[i] = -1;
      }
    }
  } else if (signal == ZERO) {
    if (start == 0) {
      for (i = end; i > 0; i--) {
	p[i] = 0;
      }
      p[0] = 0;
    } else {
      for (i = end; i >= start; i--) {
	p[i] = 0;
      }
    }
  } else {
    cit_die("cit_zerone_dec: signal error, which must be ONE or ZERO!");
  }

}
