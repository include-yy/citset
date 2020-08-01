#include "cit_def.h"

void (citFlipBit)(void * bitfield, size_t index)
{
    cit_unit * t = (cit_unit *)bitfield;
    *(t + CIT_OUT_OFFSET(index)) = cit_flip_bit(*(t + CIT_OUT_OFFSET(index)), CIT_IN_OFFSET(index));
}