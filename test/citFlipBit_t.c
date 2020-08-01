#include <stdint.h>
#include <stdio.h>
#include "citset.h"

/* test on citFlipBit(void * bitfield, size_t index) */

void print_bit(const void * bitfield, size_t start, size_t end);

int main(void)
{
    uint8_t test8 = 0;
    for (int i = 1; i < 8; i += 2)
    {
        citSetBit(&test8, i, 1);
    }
    print_bit(&test8, 0, 8), putchar('\n');
    for (int i = 0; i < 8; i++)
    {
        citFlipBit(&test8, i);
    }
    print_bit(&test8, 0, 8), putchar('\n');
    putchar('\n');
    uint16_t test16 = 0;
    for (int i = 1; i < 16; i += 2)
    {
        citSetBit(&test16, i, 1);
    }
    print_bit(&test16, 0, 16), putchar('\n');
    for (int i = 0; i < 16; i++)
    {
        citFlipBit(&test16, i);
    }
    print_bit(&test16, 0, 16), putchar('\n');
    putchar('\n');
    uint32_t test32 = 0;
    for (int i = 1; i < 32; i += 2)
    {
        citSetBit(&test32, i, 1);
    }
    print_bit(&test32, 0, 32), putchar('\n');
    for (int i = 0; i < 32; i++)
    {
        citFlipBit(&test32, i);
    }
    print_bit(&test32, 0, 32), putchar('\n');
    putchar('\n');
    uint64_t test64 = 0;
    for (int i = 1; i < 64; i += 2)
    {
        citSetBit(&test64, i, 1);
    }
    print_bit(&test64, 0, 64), putchar('\n');
    for (int i = 0; i < 64; i++)
    {
        citFlipBit(&test64, i);
    }
    print_bit(&test64, 0, 64), putchar('\n');

    return 0;
}

void print_bit(const void * bitfield, size_t start, size_t end)
{
    int per_eight = 0;
    for (; start < end; start = start + 1)
    {
        if (per_eight == 8)
        {
            putchar(' ');
            per_eight = 0;
        }
        per_eight++;
        printf("%d", citGetBit(bitfield, start));
    }
}

/* the expected result */

/*
01010101
10101010

01010101 01010101
10101010 10101010

01010101 01010101 01010101 01010101
10101010 10101010 10101010 10101010

01010101 01010101 01010101 01010101 01010101 01010101 01010101 01010101
10101010 10101010 10101010 10101010 10101010 10101010 10101010 10101010
*/