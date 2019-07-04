#include"cit_def.h"

void
cit_unit_set (cit_unit_ptr p, size_t index, int symbol)
{
  if (index >= UNITBITS) {
    cit_die("cit_unit_set: index is larger than UNITBITS");
  } else;

  if (symbol == ONE) {
    *p |= (CIT_UNIT_MSB >> index);
  } else if (symbol == ZERO) {
    *p &= (~(CIT_UNIT_MSB >> index));
  } else {
    cit_die("cit_unit_set: symbol error!");
  }

}
