#include <stdio.h>
#include "cit_def.h"

unsigned char (citGetBit)(const void * bitfield, size_t index);

void citShow(const void * bitfield, size_t start, size_t end)
{
    int per_four = 0;
    for (size_t i = start; i < end; i++)
    {
        if (per_four == 8)
        {
            putchar(' ');
            per_four = 0;
        }
        per_four += 1;
        printf("%d", citGetBit(bitfield, i));
    }
}