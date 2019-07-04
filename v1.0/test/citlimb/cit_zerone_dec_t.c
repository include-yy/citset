#include"cit_def.h"
#include"cit_limb.h"
#include<stdio.h>
/* test on cit_zerone_dec() */
/* the default WORD_SIZE is 4 */

int main(void)
{
  printf("test on cit_zerone_dec()\n");
  
  cit_unit trial[10];
  size_t i, j;
  for (i = 0; i < 10; i++) {
    printf("%u ", trial[i]);
  }
  putchar('\n');
  
  cit_zerone_dec(trial, 0, 9, ONE);
  
  for (i = 0; i < 10; i++) {
    printf("%u ", trial[i]);
  }
  putchar('\n');

  for (i = 0; i < 10; i++) {
    cit_zerone_dec(trial, i, i, ZERO);
    for (j = 0; j < 10; j++) {
      printf("%u ", trial[j]);
    }
    putchar('\n');
  }
  
  return 0;
}
