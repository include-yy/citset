#include"citset.h"
#include<stdio.h>

//trial function: citShift
/* note that there are four possibilities with this function 

                    | way | LEFT | RIGHT |
	      assign| N   |  N   |   N   |
	      ON    | N   |  1   |   2   |
	      OFF   | N   |  3   |   4   |

	      It needs several procedure to do research on it:p */

int main(void)
{
  cit a = citInit(16,ONE);
  
  // way == LEFT, assign == OFF
  cit b = citShift(a,LEFT,8,OFF);
  citShow(a,0,15),putchar('\n');
  citShow(b,0,15),putchar('\n');

  // way == LEFT, assign == ON
  citShift(a,LEFT,8,ON);
  citShow(a,0,15),putchar('\n');

  // way == RIGHT, assign == OFF
  cit c = citShift(a,RIGHT,4,OFF);
  citShow(c,0,15),putchar('\n');

  // way == RIGHT, assign == ON
  citShift(a,RIGHT,4,ON);
  citShow(a,0,15),putchar('\n');
  
  citSetAll(a,ONE);
  //what if shift-length is bigger than bits
  // a's number of bits are 16
  citShift(a,LEFT,17,ON);
  citShow(a,0,15),putchar('\n');

  citSetAll(a,ONE);
  citShift(a,RIGHT,17,ON);
  citShow(a,0,15),putchar('\n');

  citCleans(3,&a,&b,&c);

  return 0;
}
  
