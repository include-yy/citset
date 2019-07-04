#include"citset.h"
/* test on citFlip() */
int main(void)
{
  printf("test on citFlip()\n");
  cit new, old;
  citInit(new, 16, ZERO);
  citInit(old, 16, ONE);
  size_t i, j;
  
  for (i = 0,j = 1; i < 16; i += j) {
    citSet(old, i, ZERO);
    j = j + 1;
  }

  citdShow(old, 0, 15), putchar('\n');
  citdShow(new, 0, 15), putchar('\n');

  citFlip(new, old, 0, 15);
  
  citdShow(old, 0, 15), putchar('\n');
  citdShow(new, 0, 15), putchar('\n');

  citFlip(new, new, 0, 9);

  putchar('\n'), citdShow(new, 0, 15);
  
  citCleans(2, new, old);

  return 0;
}
