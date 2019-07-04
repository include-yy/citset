#include"cit_def.h"
#include"cit_limb.h"
#include"citset_in.h"

#include<stdio.h>

void
citShow (cit_ptr var, bit_index start, bit_index end, FILE * where)
{
  IndexCheck(var, end);
  if(start > end) {
    cit_die("citShow: start index bigger than end index");
  } else;
  
  bit_index i;
  for (i = start; i <= end; i++) {
    putc(citGet(var,i) + '0', where);
    if ((i + 1) % 4 == 0)
      putc(' ', where);
  }
  
}
