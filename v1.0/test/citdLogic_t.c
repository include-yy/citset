#include"citset.h"
#include<stdio.h>
/* test on citdLogic() */
int main(void)
{
  printf("test on citdLogic()\n");
  
  cit one, two, three;
  citInits(16, ONE, 3, one, two, three);
  size_t i;

  for (i = 3; i < 16; i += 3) {
    citSet(two, i, ZERO);
  }
  for (i = 1; i < 16; i += 4) {
    citSet(three, i, ZERO);
  }

  citdShow(one, 0, 15), putchar('\n');
  citdShow(two, 0, 15), putchar('\n');
  citdShow(three, 0, 15), putchar('\n');
  putchar('\n');
  
  citdLogic(one, three, two, AND);
  
  citdShow(one, 0, 15), putchar('\n');
  citdShow(two, 0, 15), putchar('\n');
  citdShow(three, 0, 15), putchar('\n');
  putchar('\n');
  
  citdLogic(one, two, three, OR);
  
  citdShow(one, 0, 15), putchar('\n');
  citdShow(two, 0, 15), putchar('\n');
  citdShow(three, 0, 15), putchar('\n');
  putchar('\n');

  citdLogic(one, two, three, XOR);
  
  citdShow(one, 0, 15), putchar('\n');
  citdShow(two, 0, 15), putchar('\n');
  citdShow(three, 0, 15), putchar('\n');
  putchar('\n');

  citdLogic(one, one, one, AND);
  citdLogic(two, two, two, OR);
  citdLogic(three, three, three, XOR);
  
  citdShow(one, 0, 15), putchar('\n');
  citdShow(two, 0, 15), putchar('\n');
  citdShow(three, 0, 15), putchar('\n');
  putchar('\n');

  citCleans(3, one ,two ,three);

  return 0;
}
