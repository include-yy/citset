#include"citset.h"

#include<stdio.h>

//trial function: citFlip
/* Note that this function has a assign argument, which means that it has the ability to modify the value of argument, you can know what it means to you by reading the trial program */

int main(void)
{
  cit a = citInit(8,ZERO);
  int i;
  for(i = 0;i < 6;i += 2)
    citSet(a,i,ONE);
  cit b = citFlip(a,OFF);
  for(i = 0;i < 8;i++)
    printf("%u ",citGet(a,i));
  putchar('\n');
  for(i = 0;i < 8;i++)
    printf("%u ",citGet(b,i));
  putchar('\n');
  citFlip(a,ON);
  for(i = 0;i < 8;i++)
    printf("%u ",citGet(a,i));
  putchar('\n');
  citCleans(2,&a,&b);
  return 0;
}
  
      
