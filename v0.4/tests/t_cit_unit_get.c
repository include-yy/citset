#include<stdio.h>
#include<limits.h>
//I have tried the three choices
#define CIT_UNIT unsigned int
#define CIT_UNIT_MSB 0x80000000
#define CIT_MAX 0xFFFFFFFF
#define UNITBITS (CHAR_BIT * (sizeof(CIT_UNIT)))

typedef CIT_UNIT* cit_unit_ptr;

//trial function: cit_unit_get

static unsigned int
cit_unit_get (cit_unit_ptr p, unsigned int index)
{
  return ((*p << index) & CIT_UNIT_MSB) >> (UNITBITS - 1);
}

int main(void)
{
  CIT_UNIT a = 0;
  unsigned int sum = 0;
  for(;a < CIT_MAX;a++)
    {
      if(cit_unit_get(&a,0))
	sum = sum + 1;
    }
  printf("%u\n",sum);
  return 0;
}
  
  
