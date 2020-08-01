#include <stdio.h>
#include <stdlib.h>
#include "citset.h"

#include<time.h>
void Me(void)
{
  static int i = 0;
  static clock_t me;
  if (i == 0) {
    me = clock();
    i = 1;
  } else if (i == 1) {
    printf("\nv1.0: time : %u\n", clock() - me);
    i = 0;
  }

}
#define NUMOFPRI 10000000

int main(void)
{
    int i, j;
    char * prime = (char*)malloc(citBOB(NUMOFPRI));
    long long int sum = 0;
    citSet(prime, 0, NUMOFPRI, 1);
    citSetBit(prime, 0, 0);
    citSetBit(prime, 1, 0);
    Me();
    for (i = 0; i < NUMOFPRI; i++) {
        if (hide8_citGetBit(prime, i) == 1) {
            for (j = i + i; j < NUMOFPRI; j += i) {
                hide8_citSetBit(prime, j, 0);
            }
        }
    }
	Me();

    for (i = 0, sum = 0; i < NUMOFPRI; i++) {
        if (hide8_citGetBit(prime, i) == 1) {
            sum += i;
        }
    }
    printf("%lld\n", sum);
   
    free(prime);
	return 0;
}