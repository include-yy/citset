#include"citset.h"
#include<stdio.h>

//trial function: citBit

/* Here are three kinds of bitwise operations: AND, OR, XOR. And here I don't use the assignment argument, because I think more argument means harder to use */

/* But I still use the assignment argument in citFlip and cit Shift, because they have only one operand */

/* note that the two operand's number of bits must be equal */
int main(void)
{
  cit a = citInit(16,ZERO);
  cit b = citInit(16,ONE);
  int i;
  for(i = 1;i < 15;i += 2)
    {
      citSet(a,i,ONE);
      citSet(b,i-1,ZERO);
    }
  citShow(a,0,15),putchar('\n');
  citShow(b,0,15),putchar('\n');

  /* AND */
  cit c = citBit(a,b,AND);
  citShow(c,0,15),putchar('\n');
  citClean(&c);

  /* OR */
  c = citBit(a,b,OR);
  citShow(c,0,15),putchar('\n');
  citClean(&c);

  /* XOR */
  c = citBit(a,b,XOR);
  citShow(c,0,15),putchar('\n');
  citClean(&c);

  citCleans(2,&a,&b);

  return 0;
}
  
