#include<stdio.h>
#include<stdlib.h>
/* Here I use unsigned char, short, int and they all pass successfully */

typedef unsigned char* cit_unit_ptr;

//trial function: cit_zerone
static void
cit_zerone (cit_unit_ptr p, unsigned int n, int signal)
{
  if(signal == 1)
    {
      while(--n > 0)
	p[n] = -1;
      p[0] = -1;
    }
  else if(signal == 0)
    {
      while(--n > 0)
	p[n] = 0;
      p[0] = 0;
    }
  /*
  else
    cit_die("cit_zerone: signal error, which must be ONE or ZERO!\n");
  //*/
}

int main(void)
{
  cit_unit_ptr p = (cit_unit_ptr)malloc(sizeof(unsigned int));
  p[0] = 233;
  cit_zerone(p, 1, 0);
  printf("%u\n",p[0]);
  cit_zerone(p, 1, 1);
  printf("%u",p[0]);
  free(p);
  return 0;
}
