#include "cit_def.h"

unsigned char (citGetBit)(const void * bitfield, size_t index)
{
    const cit_unit * t = (const cit_unit *)bitfield;
    return cit_get_bit(*(t + CIT_OUT_OFFSET(index)), CIT_IN_OFFSET(index));
}
