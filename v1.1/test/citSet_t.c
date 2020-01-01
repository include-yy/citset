#include <stdint.h>
#include <stdio.h>
#include "citset.h"

/* little-endian is required to get the expected result. (X86) */
/* test on citSet(void * bitfield, size_t start, size_t end, int symbol) */

void print_bit(const void * bitfield, size_t start, size_t end);

int main(void)
{
    uint8_t test8 = 0;
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", test8);
        citSet(&test8, i, i + 1, 1);
    }
    printf("%d\n", test8);
    putchar('\n');

    uint16_t test16 = 0;
    for (int i = 0; i < 16; i++)
    {
        printf("%d ", test16);
        citSet(&test16, i, i + 1, 1);
    }
    printf("%d\n", test16);
    putchar('\n');

    uint32_t test32 = 0;
    for (int i = 0; i < 32; i++)
    {
        printf("%u ", test32);
        citSet(&test32, i, i + 1, 1);
    }
    printf("%u\n", test32);
    putchar('\n');

    uint64_t test64 = 0;
    for (int i = 0; i < 64; i++)
    {
        printf("%llu ", test64);
        citSet(&test64, i, i + 1, 1);
    }
    printf("%llu\n", test64);
    putchar('\n');

    /* say hello */
    /* H */
    uint8_t hello[6][6] = {0};
    citSet(hello[0], 2, 4, 1);
    citSet(hello[0], 7, 9, 1);
    citSet(hello[1], 2, 4, 1);
    citSet(hello[1], 7, 9, 1);
    citSet(hello[2], 2, 9, 1);
    citSet(hello[3], 2, 9, 1);
    citSet(hello[4], 2, 4, 1);
    citSet(hello[4], 7, 9, 1);
    citSet(hello[5], 2, 4, 1);
    citSet(hello[5], 7, 9, 1);
    /* E */
    citSet(hello[0], 11, 18, 1);
    citSet(hello[1], 11, 13, 1);
    citSet(hello[2], 11, 18, 1);
    citSet(hello[3], 11, 18, 1);
    citSet(hello[4], 11, 13, 1);
    citSet(hello[5], 11, 18, 1);
    /* L */
    citSet(hello[0], 20, 22, 1);
    citSet(hello[1], 20, 22, 1);
    citSet(hello[2], 20, 22, 1);
    citSet(hello[3], 20, 22, 1);
    citSet(hello[4], 20, 22, 1);
    citSet(hello[5], 20, 27, 1);
    /* L */
    citSet(hello[0], 29, 31, 1);
    citSet(hello[1], 29, 31, 1);
    citSet(hello[2], 29, 31, 1);
    citSet(hello[3], 29, 31, 1);
    citSet(hello[4], 29, 31, 1);
    citSet(hello[5], 29, 36, 1);
    /* O */
    citSet(hello[0], 39, 44, 1);
    citSet(hello[1], 38, 40, 1);
    citSet(hello[1], 43, 45, 1);
    citSet(hello[2], 38, 40, 1);
    citSet(hello[2], 43, 45, 1);
    citSet(hello[3], 38, 40, 1);
    citSet(hello[3], 43, 45, 1);
    citSet(hello[4], 38, 40, 1);
    citSet(hello[4], 43, 45, 1);
    citSet(hello[5], 39, 44, 1);
    for (int i = 0; i < 6; i++)
    {
        print_bit(hello[i], 0, 48);
        putchar('\n');
    }

    return 0;
}

void print_bit(const void * bitfield, size_t start, size_t end)
{
    for (; start < end; start = start + 1)
    {
        printf("%d", citGetBit(bitfield, start));
    }
}

/* the expected result */

/*
citSet_t
0 128 192 224 240 248 252 254 255

0 128 192 224 240 248 252 254 255 33023 49407 57599 61695 63743 64767 65279 65535

0 128 192 224 240 248 252 254 255 33023 49407 57599 61695 63743 64767 65279 65535 8454143 12648447 14745599 15794175 16318463 16580607 16711679 16777215 2164260863 3238002687 3774873599 4043309055 4177526783 4244635647 4278190079 4294967295

0 128 192 224 240 248 252 254 255 33023 49407 57599 61695 63743 64767 65279 65535 8454143 12648447 14745599 15794175 16318463 16580607 16711679 16777215 2164260863 3238002687 3774873599 4043309055 4177526783 4244635647 4278190079 4294967295 554050781183 828928688127 966367641599 1035087118335 1069446856703 1086626725887 1095216660479 1099511627775 141836999983103 212205744160767 247390116249599 264982302294015 273778395316223 278176441827327 280375465082879 281474976710655 36310271995674623 54324670505156607 63331869759897599 67835469387268095 70087269200953343 71213169107795967 71776119061217279 72057594037927935 9295429630892703743 13907115649320091647 16212958658533785599 17365880163140632575 17942340915444056063 18230571291595767807 18374686479671623679 18446744073709551615

001100011001111111001100000001100000000111110000
001100011001100000001100000001100000001100011000
001111111001111111001100000001100000001100011000
001111111001111111001100000001100000001100011000
001100011001100000001100000001100000001100011000
001100011001111111001111111001111111000111110000
*/