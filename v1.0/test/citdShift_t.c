#include"citset.h"
#include<stdio.h>
/* test on citdShift() */
int main(void)
{
  printf("test on citdShift()\n");
  
  cit new;
  citInit(new, 16, ONE);
  citdShift(new, new, 4, LEFT);
  citdShow(new,0,15),putchar('\n');
  citdShift(new, new, 5, RIGHT);
  citdShow(new,0,15),putchar('\n');
  citdShift(new, new, 5, LEFT);
  citdShow(new,0,15),putchar('\n');
  citdShift(new, new, 4, RIGHT);
  citdShow(new,0,15),putchar('\n');
  citClean(new);

  return 0;
}
  
