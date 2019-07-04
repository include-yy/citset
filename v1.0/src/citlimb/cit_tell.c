#include"cit_def.h"

size_t cit_place[2];

void
cit_tell (bit_index index)
{
  cit_place[0] = index / UNITBITS;
  cit_place[1] = index % UNITBITS;
}
