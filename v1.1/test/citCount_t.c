#include <stdint.h>
#include <stdio.h>
#include "citset.h"

/* test on citCount(const void * bitfield, size_t start, size_t end) */

int main(void)
{
    uint8_t test8 = 1;
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", citCount(&test8, 0, 8));
        test8 = test8 * 2 + 1;
    }
    test8 += 1;
    printf("%d\n", citCount(&test8, 0, 8));

    uint16_t test16 = 1;
    for (int i = 0; i < 16; i++)
    {
        printf("%d ", citCount(&test16, 0, 16));
        test16 = test16 * 2 + 1;
    }
    test16 += 1;
    printf("%d\n", citCount(&test16, 0, 16));

    uint32_t test32 = 1;
    for (int i = 0; i < 32; i++)
    {
        printf("%d ", citCount(&test32, 0, 32));
        test32 = test32 * 2 + 1;
    }
    test32 += 1;
    printf("%d\n", citCount(&test32, 0, 32));

    uint64_t test64 = 1;
    for (int i = 0; i < 64; i++)
    {
        printf("%d ", citCount(&test64, 0, 64));
        test64 = test64 * 2 + 1;
    }
    test64 += 1;
    printf("%d\n", citCount(&test64, 0, 64));

    return 0;
}

/* the expected result */

/*
1 2 3 4 5 6 7 8 0
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 0
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 0
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 0
*/
