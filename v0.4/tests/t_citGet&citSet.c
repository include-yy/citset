#include"citset.h"
#include<stdio.h>

//trial function: citGet and citSet
//trial on both normal and abnormal
int main(void)
{
  //normal
  /*
  cit a = citInit(20,ZERO);
  int i;
  for(i = 0;i < 20;i++)
    printf("%u ",citGet(a,i));
  putchar('\n');
  for(i = 0;i < 20;i+=5)
    citSet(a,i,ONE);
  for(i = 0;i < 20;i++)
    printf("%u ",citGet(a,i));
  citClean(&a);
  return 0;
  //*/

  //abnormal-1 citGet
  /*
  cit a = citInit(20,ZERO);
  citGet(a,20);
  //*/

  //abnormal-2 citSet
  /*
  cit a = citInit(20,ZERO);
  citSet(a,20,ONE);
  //*/
}
  
    






  
}
  
  
    
