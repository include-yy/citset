#include"citset.h"
#include<unistd.h>

#define TenMb (1024*1024*8)

/* test on citInits() */

int main(void)
{
  printf("test on citInits()\n");
  
  cit old, new, mid;
  sleep(2);
  citInits(TenMb*33, ONE, 3, old, new, mid);
  sleep(2);

  citClean(old);
  sleep(1);
  citClean(new);
  sleep(1);
  citClean(mid);
  sleep(1);

  return 0;
}
