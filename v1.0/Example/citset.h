#ifndef _CITSET_H_
  #define _CITSET_H_

#include<stdint.h>
#include<stdio.h>

typedef struct
{
  uint64_t _cit_alloc;
  size_t _cit_size;
  void * _cit_limb;
}cit_in;

typedef cit_in * cit_ptr;
typedef cit_in cit[1];

void citInit(cit_ptr var, uint64_t total, int symbol);
void citInits(uint64_t total, int symbol, size_t number, cit_ptr lots, ...);
size_t citGet(cit_ptr var, uint64_t index);
void citSet(cit_ptr var, uint64_t index, int symbol);
void citSetAll(cit_ptr var, uint64_t start, uint64_t end, int symbol);
void citdSetAll(cit_ptr var, int symbol);
void citClean(cit_ptr var);
void citCleans(size_t number, cit_ptr lots, ...);

void citCopy(cit_ptr get, cit_ptr var, uint64_t start, uint64_t end);
void citdCopy(cit_ptr get, cit_ptr var);
void citFlip(cit_ptr get, cit_ptr var, uint64_t start, uint64_t end);
void citdFlip(cit_ptr get, cit_ptr var);
void citAnd(cit_ptr get, cit_ptr foo, cit_ptr bar, uint64_t start, uint64_t end);
void citOr(cit_ptr get, cit_ptr foo, cit_ptr bar, uint64_t start, uint64_t end);
void citXor(cit_ptr get, cit_ptr foo, cit_ptr bar, uint64_t start, uint64_t end);
void citdLogic(cit_ptr get, cit_ptr foo, cit_ptr bar, int signal);
void citdShift(cit_ptr get, cit_ptr var, uint64_t length, int signal);

void citShow(cit_ptr var, uint64_t start, uint64_t end, FILE * where);
void citdShow(cit_ptr var, uint64_t start, uint64_t end);

#define ONE              0X1
#define ZERO             0X0

#define AND              0X0
#define OR               0X1
#define XOR              0X2

#define LEFT             0X0
#define RIGHT            0X1

#endif
