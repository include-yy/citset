#ifndef CIT_SET_H
#define CIT_SET_H

#include <stddef.h>

#define citBOB(n) ((((n) - 1) / 8) + 1)

#define hide8_citGetBit(p, i) \
	((((*((unsigned char *)(p) + ((size_t)(i) / 8))) << ((size_t)(i) % 8)) & 0x80) >> 7)

#define hide8_citSetBit(p, i, b) \
	((*((unsigned char *)(p) + (size_t)(i) / 8)) = ((*((unsigned char *)(p) + (size_t)(i) / 8)) ^ ((-(b) ^ (*((unsigned char *)(p) + (size_t)(i) / 8))) & (0x80 >> ((size_t)(i) % 8)))))

#define hide8_citFlipBit(p, i) \
	((*((unsigned char *)(p) + ((size_t)(i) / 8))) = ((*((unsigned char *)(p) + ((size_t)(i) / 8))) ^ (0x80 >> ((size_t)(i) % 8))))

unsigned char citGetBit(const void * bitfield, size_t index);
void citSetBit(void * bitfield, size_t index, int symbol);
void citFlipBit(void * bitfield, size_t index);

size_t citCount(const void * bitfield, size_t start, size_t end);

void citGet(void * get, void * bitfield, size_t get_s, size_t bit_s, size_t n);
void citSet(void * bitfield, size_t start, size_t end, int symbol);
void citFlip(void * bitfield, size_t start, size_t end);

void citShow(const void * bitfield, size_t start, size_t end);

#endif