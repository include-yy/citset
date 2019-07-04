#include"citset.h"

/* test on citdSetAll() */

int main(void)
{
  printf("test on citdSetAll()\n");
  
  cit new;
  citInit(new, 16, ZERO);
  citdShow(new, 0, 15);
  putchar('\n');
  citdSetAll(new,ONE);
  citdShow(new, 0, 15);

  citClean(new);

  return 0;
}
