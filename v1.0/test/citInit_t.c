#include"citset.h"
#include<unistd.h>
/* test on citInit() */
/* WORD_SIZE is 4 */

/* to spy the allocation status, use the task manager */

#define TenMb (1024*1024*8*10)
int main(void)
{
  printf("test on citInit()\n");
  cit old, mid, new;
  sleep(2);
  citInit(old, TenMb*1,ONE);
  sleep(1);
  citInit(mid, TenMb*2,ZERO);
  sleep(1);
  citInit(new, TenMb*3,ZERO);
  sleep(1);
  citClean(new);
  sleep(1);
  citClean(mid);
  sleep(1);
  citClean(old);
  sleep(1);

  return 0;
}
  

  
