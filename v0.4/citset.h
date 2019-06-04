#ifndef __CITSET_H__
  #define __CITSET_H__
/*

citset library - manipualte bit just like C++'s <bitset>.

This library is an implementation of multi-bit manipulation.

As it is named bitset in C++, I use the name citset :p

*/

#include<stdint.h>
#include<stdio.h>
#include<limits.h>


/* This macro defines the word size in bytes of unit that constitues the bits data structure. */

#ifndef CIT_WORD_SIZE
  #define CIT_WORD_SIZE 4
#endif

/* Here comes the compile-time specialization for how large the underlying unit size should be. */
/* The choices are 1, 2 and 4 bytes */

#ifndef CIT_WORD_SIZE
   #error Must define CIT_WORD_SIZE to be 1, 2, 4
#elif (CIT_WORD_SIZE == 1)
  /* Date type of unit in structure */
  #define CIT_UNIT                uint8_t
  /* bitmask for getting MSB (MSB is the abbr of Most Significant Bit) */
  #define CIT_UNIT_MSB            ((CIT_UNIT)0x80)
  /* Max value of unit's type */
  #define CIT_UNIT_MAX            ((CIT_UNIT)0xFF)
#elif (CIT_WORD_SIZE == 2)
  #define CIT_UNIT                uint16_t
  #define CIT_UNIT_MSB            ((CIT_UNIT)0x8000)
  #define CIT_UNIT_MAX            ((CIT_UNIT)0xFFFF)
#elif (CIT_WORD_SIZE == 4)
  #define CIT_UNIT                uint32_t
  #define CIT_UNIT_MSB            ((CIT_UNIT)0x80000000)
  #define CIT_UNIT_MAX            ((CIT_UNIT)0xFFFFFFFF)
#endif
#ifndef CIT_UNIT
  #error CIT_UNIT must be defined to uint8_t, uint16_t uint32_t or whatever
#endif

/* the number of bits that one unit have */
#define UNITBITS (CIT_WORD_SIZE * CHAR_BIT)

typedef CIT_UNIT * cit_unit_ptr;

/* logic operators macro */
#define AND                       0X0
#define OR                        0X1
#define XOR                       0X2

#define RIGHT                     0X0
#define LEFT                      0X1

/* ZERO and ONE are booleans that indicate the value of 1 bit, ONE for 1 and ZERO for 0. */
#define ZERO                      0X0
#define ONE                       0X1

/* ON and OFF indicate some function's behaviour, if ON is used, it means that assignment will be taken. */
#define ON                        0X0
#define OFF                       0X1

typedef struct 
{
  unsigned int _cit_alloc;        /* Number of *bits* allocated and pointed
				     to by the _cit_limb field.  */
  unsigned int _cit_size;         /* Number of *units* allocated and pointed
				     to by the _cit_limb field.  */
  
  cit_unit_ptr _cit_limb;           /* Pointer to the limb */
}cit;

/* Initialization functions: */
cit citInit(unsigned int total, int symbol);
void citInits (unsigned int total, int symbol, unsigned int number, cit * lots, ...);

/* Basic operation function: */
unsigned int citGet(cit var, unsigned int index);
void citSet(cit var, unsigned int index, int symbol);
void citSetAll(cit var, int symbol);
cit citCopy(cit old);
void citClean(cit * var);
void citCleans(unsigned int number, cit * lots, ...);

/* Bitwise operation functions: */
cit citFlip(cit var, int assign_or_not);
cit citShift(cit var, int way, unsigned int length, int assign_or_not);
cit citBit(cit first, cit second, int symbol);

/* I/O funtions: */
void citfShow(cit var, unsigned int start, unsigned int end, FILE * where);
void citShow(cit var, unsigned int start,unsigned int end);
cit citinStr(char * str);
void citinUnit(cit Getit, unsigned int index, CIT_UNIT compound);

#endif
