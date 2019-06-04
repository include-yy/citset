#include"citset.h"
#include<stdio.h>
#include<string.h>
//trial function: citinStr

/* the behaviour is that: all character except '0' are recognized as '1' */

int main(void)
{
  cit a = citinStr("1001001001");
  citShow(a,0,strlen("1001001001")-1);
  putchar('\n');
  cit b = citinStr("abcdef0");
  citShow(b,0,strlen("abcdef0")-1);
  citCleans(2,&a,&b);

  return 0;
}
