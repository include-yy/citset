#include<unistd.h>
#include"citset.h"

/* test on citCleans() */

#define OneMb (1024 * 1024 * 8)

int main(void)
{
  printf("test on citCleans()\n");
  
  cit new, old ,mid;
  
  citInits(OneMb, ONE, 3, new, old, mid);
  sleep(3);
  citCleans(3, new, old, mid);
  sleep(2);
  
  return 0;
}
