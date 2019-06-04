#include<stdio.h>

//Here, I try 8, 16 and 32, they all work well. */
#define UNITBITS 8

//trial function: cit_tell
static unsigned int cit_place[2];

static void
cit_tell (unsigned int index)
{
  cit_place[0] = index / UNITBITS;
  cit_place[1] = index % UNITBITS;
}

int main(void)
{
  int i;
  for(i = 0;i <= UNITBITS;i++)
    {
      cit_tell(i);
      printf("%u %u\n",cit_place[0],cit_place[1]);
    }
  return 0;
}
