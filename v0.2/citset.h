#ifndef _CITSET_
#define _CITSET_


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

typedef void* cit;
typedef unsigned int SCALAR;
typedef unsigned char STDUNIT;
typedef int loop_t;

#define AND 0
#define OR 1
#define XOR 2
#define RIGHT 0
#define LEFT 1
#define ZERO 0
#define ONE 1
#define STDUNIT_MAX 0XFFU
#define HIGH_ORDER ((STDUNIT)(~(STDUNIT_MAX>>1)))
#define HeadField sizeof(SCALAR)
#define BitField sizeof(STDUNIT)
#define BitLength (sizeof(STDUNIT) * CHAR_BIT)

#define MIN(a, b) (a > b? a: b)

#define IndexCheck(varm, index) do {		\
    if(index >= citSize(varm))			\
      {						\
	puts("index error!");			\
	exit(EXIT_FAILURE);			\
      }						\
  } while(0)

cit citInit(SCALAR total, _Bool signal);
cit citStr(char * liter);
SCALAR citSize(cit varm);
SCALAR* citTell(cit varm, SCALAR index);
SCALAR citGet(cit varm, SCALAR index);
void citSet(cit varm, SCALAR index, _Bool signal);
cit citCopy(cit varm);
void citClean(cit varm);
SCALAR citCount(cit varm);
void citFlip(cit varm, SCALAR index);
void citFlipa(cit varm);
cit citShift(cit varm, SCALAR dis, SCALAR way);
cit citBit(cit first, cit second, SCALAR op);
void citShow(cit varm, SCALAR items, FILE * where);

#endif
