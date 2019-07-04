#include"citset.h"
#include<unistd.h>
#define TenMb (1024*1024*8*10)

/* test on citClean() */

int main(void)
{
  printf("test on citClean()\n");
  
  cit new;
  citInit(new, (size_t)TenMb*20, ONE);

  sleep(3);

  citClean(new);

  sleep(3);

  return 0;
}
