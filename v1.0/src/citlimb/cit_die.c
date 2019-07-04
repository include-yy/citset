#include<stdio.h>
#include<stdlib.h>

void
cit_die (char * msg)
{
  fprintf(stderr, "%s\n", msg);
  abort();
}
