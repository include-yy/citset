#include"citset.h"
#include<stdio.h>

/* test on citSetAll() */

int main(void)
{
  printf("test on citSetAll()\n");
  
  cit new;
  citInit(new,32, ONE);
  citdShow(new,0,31);
  putchar('\n');
  citSetAll(new,7, 23, ZERO);
  citdShow(new,0,31);
  putchar('\n');

  citClean(new);

  return 0;
}
