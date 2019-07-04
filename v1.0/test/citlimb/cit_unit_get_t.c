#include"cit_def.h"
#include"cit_limb.h"
#include<stdio.h>
/* test on cit_unit_get() */
/* the default WORD_SIZE is 4 */

int main(void)
{
  printf("test on cit_unit_get()\n");

  cit_unit uni = -1;

  size_t i;
  for (i = 0; i < UNITBITS; i++) {
    printf("%u",cit_unit_get(&uni, i));
  }

  return 0;
}
