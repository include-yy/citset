#include"citset.h"
#include<stdio.h>

//trial function: citinUnit

/* the behviour is that: put a unit into the bits */

int main(void)
{
  //the WORD_SIZE is assumed to be 4
  cit a = citInit(32*2,ZERO);
  CIT_UNIT in = 0xFFFFFFFF;
  int i;
  for(i = 0;i < 2;i++)
    citinUnit(a,i,in);
  citShow(a,0,63);
  //abnomal
  /*
  citinUnit(a,3,in);
  //*/
  citClean(&a);
  return 0;
  
}
    
