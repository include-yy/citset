#include"citset.h"

/* test on citGet() */

int main(void)
{
  printf("test on citGet()\n");
  cit new;
  citInit(new, 16, ONE);
  size_t i;
  for (i = 0; i < 16; i++) {
    printf("%u",citGet(new, i));
  }
  putchar('\n');
  citdShow(new, 0, 15);

  citClean(new);

  return 0;
}
