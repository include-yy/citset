#include"cit_def.h"
#include"cit_limb.h"
#include<stdio.h>
/* test on cit_unit_set() */
/* the default WORD_SIZE is 4 */

int main(void)
{
  printf("test on cit_unit_set()\n");

  cit_unit uni = -1;

  size_t i;
  printf("%u ",uni);
  for (i = 0; i < UNITBITS; i++) {
    cit_unit_set(&uni, i, ZERO);
    printf("%u ",uni);
  }
  putchar('\n');
  for (i = UNITBITS - 1; i > 0; i--) {
    cit_unit_set(&uni, i, ONE);
    printf("%u ",uni);
  }
  cit_unit_set(&uni, 0, ONE);
  printf("%u\n",uni);
  
  return 0;
}
