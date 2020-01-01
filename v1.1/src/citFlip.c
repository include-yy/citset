#include "cit_def.h"

void citFlip(void * bitfield, size_t start, size_t end)
{
    cit_unit * t = bitfield;
    size_t out_s = CIT_OUT_OFFSET(start);
    size_t out_e = CIT_OUT_OFFSET(end);

    if (out_s == out_e)
    {
        *(t + out_s) = cit_flip(*(t + out_s), CIT_IN_OFFSET(start), CIT_IN_OFFSET(end));
    }
    else
    {
        *(t + out_s) = cit_flip(*(t + out_s), CIT_IN_OFFSET(start), CIT_UNIT_BIT);
        while (++out_s < out_e)
        {
            *(t + out_s) = cit_flip(*(t + out_s), 0, CIT_UNIT_BIT);
        }
        if (CIT_IN_OFFSET(end))
        {
            *(t + out_e) = cit_flip(*(t + out_e), 0, CIT_IN_OFFSET(end));
        }
    }
}