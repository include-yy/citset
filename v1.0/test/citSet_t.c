#include"citset.h"

/* test on citSet() */

int main(void)
{
  printf("test on citSet()\n");
  
  cit new;
  citInit(new, 16, ONE);
  size_t i;

  for (i = 0; i < 16; i+=2) {
    citSet(new, i, ZERO);
  }
  citdShow(new, 0, 15);

  citClean(new);

  return 0;
}
