#include"citSet.h"
#include<stdio.h>

//trial function: citSetAll

int main(void)
{
  cit a = citInit(23,ZERO);
  int i;
  for(i = 0;i < 23;i++)
    printf("%u ",citGet(a,i));
  putchar('\n');
  citSetAll(a,ONE);
  for(i = 0;i < 23;i++)
    printf("%u ",citGet(a,i));
  putchar('\n');
  citSetAll(a,ZERO);
  for(i = 0;i < 23;i++)
    printf("%u ",citGet(a,i));
  putchar('\n');
  
  citClean(&a);
  return 0;
}
  
