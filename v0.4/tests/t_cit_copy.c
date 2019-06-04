#include<stdio.h>
#include<stdlib.h>

//options: char short int
#define CIT_UNIT unsigned int

typedef CIT_UNIT* cit_unit_ptr;

//trial function: cit_copy
static void
cit_copy (cit_unit_ptr d, cit_unit_ptr s ,unsigned int n)
{
  unsigned int i;
  
  for(i = 0;i < n;i++)
    d[i] = s[i];
}

int main(void)
{
  cit_unit_ptr a = malloc(sizeof(CIT_UNIT)*23);
  cit_unit_ptr b = malloc(sizeof(CIT_UNIT)*23);

  unsigned int i;
  for(i = 0;i < 23;i++)
    a[i] = i;
  cit_copy(b,a,23);
  for(i = 0;i < 23;i++)
    printf("%u ",a[i]);
  putchar('\n');
  for(i = 0;i < 23;i++)
    printf("%u ",b[i]);
  free(a),free(b);
  return 0;
}
  
