#include"citset.h"
/* test on citdCopy() */
int main(void)
{
  printf("test on citdCopy()\n");
  
  cit new, old;
  
  citInit(new, 16, ONE);
  citInit(old, 16, ZERO);

  citdShow(new, 0, 15), putchar('\n');
  citdShow(old, 0, 15), putchar('\n');
  
  citdCopy(new, old);

  citdShow(new, 0, 15), putchar('\n');
  citdShow(old, 0, 15), putchar('\n');

  citCleans(2, new, old);

  return 0;
}
