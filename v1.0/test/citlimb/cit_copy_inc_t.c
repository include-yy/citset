#include"cit_def.h"
#include"cit_limb.h"
#include<stdio.h>
/* test on cit_copy_inc() */
/* the default WORD_SIZE is 4 */

int main(void)
{
  printf("test on cit_copy_inc()\n");
  
  cit_unit trial[10];
  cit_unit test[10];
  size_t i, j;

  for (i = 0; i < 10; i++) {
    trial[i] = 0;
    test[i] = 1;
  }

  for (i = 0; i < 10; i++) {
    printf("%u ",trial[i]);
  }
  putchar('\n');
  for (i = 0; i < 10; i++) {
    printf("%u ",test[i]);
  }
  putchar('\n'), putchar('\n');
  
  for (i = 0; i < 5; i++) {
    cit_copy_inc(trial, test, i, i);
    for (j = 0; j < 10; j++) {
      printf("%u ", trial[j]);
    }
    putchar('\n');
  }
  
  cit_copy_inc(test, trial, 5, 9);

  for (i = 0; i < 10; i++) {
    printf("%u ",trial[i]);
  }
  putchar('\n');
  for (i = 0; i < 10; i++) {
    printf("%u ",test[i]);
  }
  
  return 0;
}
