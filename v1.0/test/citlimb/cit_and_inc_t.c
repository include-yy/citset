#include"cit_def.h"
#include"cit_limb.h"
#include<stdio.h>
/* test on cit_and_inc() */
/* the default WORD_SIZE is 4 */

int main(void)
{
  printf("test on cit_and_inc()\n");

  cit_unit fst[10];
  cit_unit sec[10];
  cit_unit thr[10];
  size_t i;;
  
  for (i = 0; i < 10; i++) {
    fst[i] = 0;
    thr[i] = 1;
    if ((i + 1) % 2 == 0) {
      sec[i] = 1;
    } else {
      sec[i] = 0;
    }
  }

  for (i = 0; i < 10; i++) {
    printf("%u ", fst[i]);
  }
  putchar('\n');
  for (i = 0; i < 10; i++) {
    printf("%u ", sec[i]);
  }
  putchar('\n');
  for (i = 0; i < 10; i++) {
    printf("%u ", thr[i]);
  }
  putchar('\n');

  cit_and_inc(sec, thr, 0, 9, fst);

  for (i = 0; i < 10; i++) {
    printf("%u ", fst[i]);
  }
  putchar('\n');
  for (i = 0; i < 5; i++) {
    thr[i] = 0;
  }
  cit_and_inc(fst, thr, 0, 9, fst);

  for (i = 0; i < 10; i++) {
    printf("%u ", fst[i]);
  }
  putchar('\n');

  return 0;
}
