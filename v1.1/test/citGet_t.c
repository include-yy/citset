#include <stdint.h>
#include <stdio.h>
#include "citset.h"

/* little-endian is required to get the expected result. (X86) */
/* test on citGet(void * get, void * bitfield, size_t get_s, size_t bit_s, size_t n) */

void print_bit(const void * bitfield, size_t start, size_t end);

int main(void)
{
    uint8_t org1 = 0xf0;
    uint8_t get1 = 0;
    citSetBit(&org1, 5, 1);

    citGet(&get1, &org1, 0, 2, 4);
    print_bit(&org1, 0, 8), putchar('\n');
    print_bit(&get1, 0, 8), putchar('\n');

    uint16_t org2 = 0xf00f;
    uint16_t get2 = 0;
    citSet(&org2, 6, 10, 0);
    citGet(&get2, &org2, 2, 5, 6);
    print_bit(&org2, 0, 16), putchar('\n');
    print_bit(&get2, 0, 16), putchar('\n');

    citGet(&get2, &org2, 7, 4, 4);
    print_bit(&org2, 0, 16), putchar('\n');
    print_bit(&get2, 0, 16), putchar('\n');

    citGet(&get2, &org2, 7, 4, 8);
    print_bit(&org2, 0, 16), putchar('\n');
    print_bit(&get2, 0, 16), putchar('\n');

    uint8_t testarr[8] = {0};
    citSet(testarr, 32, 64, 1);
    print_bit(testarr, 0, 64), putchar('\n');
    citGet(testarr, testarr + 4, 0, 0, 32);
    print_bit(testarr, 0, 64), putchar('\n');

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
citGet_t
11110100
11010000
00001100 00110000
00100001 00000000
00001100 00110000
00100001 10000000
00001100 00110000
00100001 10000110
00000000 00000000 00000000 00000000 11111111 11111111 11111111 11111111
11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111
*/