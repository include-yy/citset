#include"citset.h"
#include<stdio.h>
/* test on citAnd() */
int main(void)
{
  printf("test on citAnd()\n");
  
  cit new, old, now;
  citInit(now, 16, ZERO);
  citInits(16, ONE, 2, new, old);
  size_t i;

  for (i = 0; i < 16; i+=3) {
    citSet(old, i, ZERO);
  }
  for (i = 0; i < 16; i += 2) {
    citSet(new, i, ZERO);
  }

  citdShow(now, 0, 15), putchar('\n');
  citdShow(old, 0, 15), putchar('\n');
  citdShow(new, 0, 15), putchar('\n');
  putchar('\n');

  citAnd(now, new, old, 2, 8);
  
  citdShow(now, 0, 15), putchar('\n');
  citdShow(old, 0, 15), putchar('\n');
  citdShow(new, 0, 15), putchar('\n');
  putchar('\n');

  citAnd(new, new, old, 0, 15);
  
  citdShow(now, 0, 15), putchar('\n');
  citdShow(old, 0, 15), putchar('\n');
  citdShow(new, 0, 15), putchar('\n');
  putchar('\n');

  citCleans(3, new, old, now);

  return 0;
}
