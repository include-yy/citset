#include"cit_def.h"
#include"cit_limb.h"
#include"citset_in.h"
#include<stdarg.h>
void
citCleans (size_t number, cit_ptr lots, ...)
{
  if (number == 0) {
    cit_die("cit_Cleans: number of object to be cleaned is zero!");
  } else;

  va_list lis;
  size_t i;
  cit_ptr var;

  va_start(lis, lots);
  citClean(lots);
  for (i = 0; i < number - 1; i++) {
    var = va_arg(lis, cit_ptr);
    citClean(var);
  }
  
  va_end(lis);
  
}
