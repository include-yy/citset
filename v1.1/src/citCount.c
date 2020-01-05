#include "cit_def.h"

size_t (citCount)(const void * bitfield, size_t start, size_t end)
{
    const cit_unit * t = (const cit_unit *)bitfield;
    size_t count = 0;
    size_t out_s = CIT_OUT_OFFSET(start);
    size_t out_e = CIT_OUT_OFFSET(end);

    if (out_s == out_e)
    {
        return cit_count(cit_get(*(t + out_s), CIT_IN_OFFSET(start), CIT_IN_OFFSET(end), 0));
    }
    else
    {
        count = cit_count(cit_get(*(t + out_s), CIT_IN_OFFSET(start), CIT_UNIT_BIT, 0));
        while (++out_s < out_e)
        {
            count += cit_count(*(t + out_s));
        }
        if (CIT_IN_OFFSET(end))
        {
            count += cit_count(cit_get(*(t + out_e), 0, CIT_IN_OFFSET(end), 0));
        }
        return count;
    }
}