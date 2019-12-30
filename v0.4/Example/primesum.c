#include"citset.h"
#include<stdio.h>
#define TAX 10000000
#include<time.h>

void Me(void)
{
  static int i = 0;
  static clock_t me;
  if(i == 0)
    {
      i = 1;
      me = clock();
    }
  else if(i == 1)
    {
      printf("\ntime:%u\n",clock() - me);
      i = 0;
    }
}
int main(void)
{
  cit prime = citInit(TAX, ONE);
  unsigned int i, j;
  long long int sum = 0;
  citSet(prime,0,ZERO);
  citSet(prime,1,ZERO);

  Me();
  for(i = 0;i < TAX;i++)
    {
      if(citGet(prime,i))
	{
	  for(j = i + i;j < TAX;j += i)
	    citSet(prime,j,ZERO);
	}
    }
  Me();
  for(i = 0;i < TAX;i++)
    {
      if(citGet(prime,i))
	sum += i;
    }
  
  printf("The sum is : %lld",sum);

  citClean(&prime);
  return 0;
}
  
