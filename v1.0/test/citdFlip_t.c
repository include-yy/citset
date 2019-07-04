#include"citset.h"
/* test on citdFlip() */
int main(void)
{
  printf("test on citdFlip()\n");
  
  cit new;
  cit old;

  citInits(16, ONE, 2, new, old);

  citdShow(new, 0, 15), putchar('\n');
  citdShow(old, 0, 15), putchar('\n');
  
  citdFlip(old, new);
  
  citdShow(new, 0, 15), putchar('\n');
  citdShow(old, 0, 15), putchar('\n');

  citdFlip(old, old);

  citdShow(new, 0, 15), putchar('\n');
  citdShow(old, 0, 15), putchar('\n');

  citCleans(2, new, old);

  return 0;
}
