#include"citset.h"

#include<stdio.h>

//trial function: citCopy

int main(void)
{
  cit a = citInit(10,ZERO);
  int i;
  for(i = 0;i < 10;i+=2)
    citSet(a,i,ONE);
  cit b = citCopy(a);
  for(i = 0;i < 10;i++)
    {
      printf("%u ",citGet(a,i));
    }
  putchar('\n');
  for(i = 0;i < 10;i++)
    {
      printf("%u ",citGet(b,i));
    }
  citCleans(2,&a,&b);
  return 0;
}
