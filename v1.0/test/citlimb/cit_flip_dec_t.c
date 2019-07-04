#include"cit_def.h"
#include"cit_limb.h"
#include<stdio.h>
/* test on cit_flip_dec() */
/* the default WORD_SIZE is 4 */

int main(void)
{
  printf("test on cit_flip_dec()\n");
  
  cit_unit trial[10];
  size_t i, j;
  for (i = 0; i < 10; i++) {
    trial[i] = 0;
  }

  for (i = 0; i < 10; i++) {
    cit_flip_dec(trial, trial, i, i);
    for (j = 0; j < 10; j++) {
      printf("%u ", trial[j]);
    }
    putchar('\n');
  }

  cit_flip_dec(trial, trial, 0, 9);
  for (j = 0; j < 10; j++) {
    printf("%u ", trial[j]);
  }
  putchar('\n');

  cit_unit other[10];
  cit_flip_dec(other, trial, 0, 9);
  for (j = 0; j < 10; j++) {
    printf("%u ", other[j]);
  }
  putchar('\n');

  return 0;
}
