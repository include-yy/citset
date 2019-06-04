#include<stdio.h>
#include<limits.h>

//I try the three choice of WORD_SIZE 1, 2, 4
#define CIT_UNIT_MSB 0x80000000
#define CIT_UNIT unsigned int
#define BITS (CHAR_BIT*(sizeof(CIT_UNIT)))

typedef CIT_UNIT * cit_unit_ptr;

static void
cit_unit_set (cit_unit_ptr p, unsigned int index, int symbol)
{
  if(symbol == 1)
    {
      *p |= (CIT_UNIT_MSB >> index);
    }
  else if(symbol == 0)
    {
      *p &= (~(CIT_UNIT_MSB >> index));
    }
  /*
  else
    {
      cit_die("cit_unit_set: symbol error!\n");
    }
  //*/
}

int main(void)
{
  CIT_UNIT a = 0;
  int i;
  for(i = BITS - 1;i >= 0;i--)
    {
      cit_unit_set(&a, i, 1);
      printf("%u ",a);
    }
  putchar('\n');
  for(i = BITS - 1;i >= 0;i--)
    {
      cit_unit_set(&a, i, 0);
      printf("%u ",a);
    }
  return 0;
}
 
