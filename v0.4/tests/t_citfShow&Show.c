#include<stdio.h>
#include"citset.h"

//trial function: citfShow and citShow

int main(void)
{
  cit c = citInit(8,ONE);
  int i;
  for(i = 5; i < 8;i+=2)
    {
      citSet(c,i,ZERO);
    }
  //citfShow
  for(i = 0;i <= 7;i++)
    {
      citfShow(c,0,i,stdout);
      putchar('\n');
    }
  //citShow
  for(i = 7;i >= 0;i--)
    {
      citShow(c,0,i);
      putchar('\n');
    }
  citClean(&c);

  return 0;
}
      
