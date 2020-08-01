#include "cit_def.h"

static inline void getit(cit_unit * g,
                         cit_unit * t,
                         size_t out_bc,
                         size_t out_be,
                         size_t in_bc,
                         size_t in_be,
                         size_t out_gc,
                         size_t out_ge,
                         size_t in_gc,
                         size_t in_ge);

void (citGet)(void * get, void * bitfield, size_t get_s, size_t bit_s, size_t n)
{
    if (n == 0)
    {
        return;
    }

    cit_unit * g = (cit_unit *)get;
    cit_unit * t = (cit_unit *)bitfield;

    size_t out_bc = CIT_OUT_OFFSET(bit_s);
    size_t in_bc = CIT_IN_OFFSET(bit_s);

    size_t out_gc = CIT_OUT_OFFSET(get_s);
    size_t in_gc = CIT_IN_OFFSET(get_s);

    if (in_gc + n <= CIT_UNIT_BIT)
    {
        *(g + out_gc) = cit_zerone(*(g + out_gc), in_gc, in_gc + n, 0);
        if (in_bc + n <= CIT_UNIT_BIT)
        {
            *(g + out_gc) |= cit_get(*(t + out_bc), in_bc, in_bc + n, in_gc);
        }
        else
        {
            *(g + out_gc) |= (cit_get(*(t + out_bc), in_bc, CIT_UNIT_BIT, in_gc) |
                              cit_get(*(t + out_bc + 1), 0, n - (CIT_UNIT_BIT - in_bc), in_gc + (CIT_UNIT_BIT - in_bc)));
        }
    }
    else
    {
        *(g + out_gc) = cit_zerone(*(g + out_gc), in_gc, CIT_UNIT_BIT, 0);
        if (in_bc + n <= CIT_UNIT_BIT)
        {

            *(g + out_gc) |= cit_get(*(t + out_bc), in_bc, in_bc + (CIT_UNIT_BIT - in_gc), in_gc);
            *(g + out_gc + 1) = cit_zerone(*(g + out_gc + 1), 0, n - (CIT_UNIT_BIT - in_gc), 0);
            *(g + out_gc + 1) |= cit_get(*(t + out_bc), in_bc + (CIT_UNIT_BIT - in_gc), in_bc + n, 0);
        }
        else
        {
            getit(g,
                  t,
                  out_bc,
                  CIT_OUT_OFFSET(bit_s + n),
                  in_bc,
                  CIT_IN_OFFSET(bit_s + n),
                  out_gc,
                  CIT_OUT_OFFSET(get_s + n),
                  in_gc,
                  CIT_IN_OFFSET(get_s + n));
        }
    }
}

static inline void getit(cit_unit * g,
                         cit_unit * t,
                         size_t out_bc,
                         size_t out_be,
                         size_t in_bc,
                         size_t in_be,
                         size_t out_gc,
                         size_t out_ge,
                         size_t in_gc,
                         size_t in_ge)
{
    if (in_gc > in_bc)
    {
        *(g + out_bc) |= cit_get(*(t + out_bc), in_bc, in_bc + (CIT_UNIT_BIT - in_gc), in_gc);
        in_bc += (CIT_UNIT_BIT - in_gc);
        out_gc += 1;
        in_gc = 0;
        while (out_gc < out_ge)
        {
            *(g + out_gc) = (cit_get(*(t + out_bc), in_bc, CIT_UNIT_BIT, 0) |
                             cit_get(*(t + out_bc + 1), 0, in_bc, CIT_UNIT_BIT - in_bc));
            out_gc += 1;
            out_bc += 1;
        }
        citGet(g + out_gc, t + out_bc, in_gc, in_bc, in_ge);
    }
    else if (in_gc == in_bc)
    {
        *(g + out_gc) |= cit_get(*(t + out_bc), in_bc, CIT_UNIT_BIT, in_gc);
        out_gc += 1;
        in_gc = 0;
        out_bc += 1;
        in_bc = 0;
        while (out_gc < out_ge)
        {
            *(g + out_gc) = *(t + out_bc);
            out_gc += 1;
            out_bc += 1;
        }
        citGet(g + out_gc, t + out_bc, in_gc, in_bc, in_ge);
    }
    else
    {
        *(g + out_gc) |= (cit_get(*(t + out_bc), in_bc, CIT_UNIT_BIT, in_gc) |
                          cit_get(*(t + out_bc + 1), 0, in_bc - in_gc, in_gc + (CIT_UNIT_BIT - in_bc)));
        out_bc += 1;
        in_bc = in_bc - in_gc;
        out_gc += 1;
        in_gc = 0;
        while (out_gc < out_ge)
        {
            *(g + out_bc) = (cit_get(*(t + out_bc), in_bc, CIT_UNIT_BIT, 0) |
                             cit_get(*(t + out_bc + 1), 0, in_bc, CIT_UNIT_BIT - in_bc));
            out_gc += 1;
            out_bc += 1;
        }
        citGet(g + out_gc, t + out_bc, in_gc, in_bc, in_ge);
    }
}