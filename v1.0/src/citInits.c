#include<stdarg.h>
#include"cit_def.h"
#include"cit_limb.h"
#include"citset_in.h"

void
citInits (bit_index total, int symbol, size_t number, cit_ptr lots, ...)
{
  va_list lis;
  size_t i;
  cit_ptr var = NULL;

  va_start(lis, lots);
  citInit(lots, total, symbol);

  for (i = 0; i < number - 1; i++) {
    var = va_arg(lis, cit_ptr);
    citInit(var, total, symbol);
  }

  va_end(lis);

}
