#include "cit_def.h"

void citSetBit(void * bitfield, size_t index, int symbol)
{
    cit_unit * t = (cit_unit *)bitfield;
    *(t + CIT_OUT_OFFSET(index)) = cit_set_bit(*(t + CIT_OUT_OFFSET(index)), CIT_IN_OFFSET(index), symbol);
}
