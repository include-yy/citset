#include"citset.h"
#include<stdio.h>
#include<time.h>
void Me(void)
{
  static int i = 0;
  static clock_t me;
  if (i == 0) {
    me = clock();
    i = 1;
  } else if (i == 1) {
    printf("\nv1.0: time : %u\n",clock() - me);
    i = 0;
  }

}

#define NUMOFPRI 10000000

int main(void)
{
  cit prime;
  long long int sum;
  unsigned int i, j;
  citInit(prime, NUMOFPRI, ONE);
  citSetAll(prime, 0, 1, ZERO);
  
  Me();
  for (i = 0; i < NUMOFPRI; i++) {
    if (citGet(prime, i) == ONE) {
      for (j = i + i; j < NUMOFPRI; j += i) {
	citSet(prime, j, ZERO);
      }
    }
  }
  Me();
  
  for (i = 0, sum = 0; i < NUMOFPRI; i++) {
    if (citGet(prime, i) == ONE) {
      sum += i;
    }
  }

  printf("The sum is : %lld\n", sum);

  citClean(prime);

  return 0;
}
