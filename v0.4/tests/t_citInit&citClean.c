#include"citset.h"
#include<stdio.h>
#include<stdlib.h>

#include<unistd.h>

//trial function: citInit and citInits
//trial function: citClean and citCleans

/* The Behaviour of these four funcitons is not print-able, so it is necessary to use the task manager(I'am on the windows. There must be some differences between Linux and Windows.) to monitor the allocation of memory. */

/* Here I use the sleep() to make the allocation more obvious to look. */

int main(void)
{
  cit one,two,three;
  // 1M = 1024 KB = 1024 * 1024 B = 1024 * 1024 * 8 BITS;
  /* trial on citInit and citClean */
  one = citInit(1024*1024*8*10,ONE);
  printf("%u ", one._cit_limb[0]);
  fflush(stdout);
  sleep(2);
  citClean(&one);
  sleep(1);
  one = citInit(1024*1024*8*20, ZERO);
  printf("%u \n",one._cit_limb[0]);
  fflush(stdout);
  sleep(2);
  citClean(&one);
  /* trial end */
  sleep(1);
  /* trial on citInits and citCleans */
  citInits(1024*1024*8*33, ONE, 3, &one, &two, &three);
  printf("%u %u %u\n",one._cit_limb[0],two._cit_limb[0],three._cit_limb[0]);
  fflush(stdout);
  sleep(2);
  citCleans(3, &one, &two, &three);
  sleep(1);
  citInits(1024*1024*8*33, ZERO, 3, &one, &two, &three);
  printf("%u %u %u\n",one._cit_limb[0],two._cit_limb[0],three._cit_limb[0]);
  fflush(stdout);
  sleep(2);
  citCleans(2, &one, &two);
  sleep(2);
  citCleans(1,&three);
  sleep(1);
  return 0;
}
  
