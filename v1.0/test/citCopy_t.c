#include"citset.h"

/* test on citCopy() */

int main(void)
{
  printf("test on citCopy()\n");
  
  cit new, old;
  
  citInit(new, 16, ZERO);
  citInit(old, 16, ONE);

  citdShow(new, 0, 15), putchar('\n');
  citdShow(old, 0, 15), putchar('\n');
  
  citCopy(new, old, 5, 10);

  citdShow(new, 0, 15), putchar('\n');
  citdShow(old, 0, 15), putchar('\n');

  citCleans(2, new, old);

  return 0;
}
