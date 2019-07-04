#ifndef _CITSET_IN_
  #define _CITSET_IN_

#include<stdint.h>
#include<stdio.h>
#include"cit_def.h"

typedef struct
{
  uint64_t _cit_alloc;
  size_t _cit_size;
  void * _cit_limb;
}cit_in;

typedef cit_in * cit_ptr;
typedef cit_in cit[1];

#define EqualCheck(foo, bar) do {			\
    if (((foo)->_cit_alloc != (bar)->_cit_alloc) ||	\
	((foo)->_cit_size != (bar)->_cit_size)) {	\
      fprintf(stderr,"%s: ", __FILE__);			\
      cit_die("two struct is not equal!");		\
    }							\
  } while(0);

#define IndexCheck(foo, index) do {		\
    if ((index) > (foo)->_cit_alloc) {		\
      fprintf(stderr, "%s: ", __FILE__);	\
      cit_die("index error!");			\
    }						\
  } while(0);

void citInit(cit_ptr var, bit_index total, int symbol);
void citInits(bit_index total, int symbol, size_t number, cit_ptr lots, ...);
size_t citGet(cit_ptr var, bit_index index);
void citSet(cit_ptr var, bit_index index, int symbol);
void citSetAll(cit_ptr var, bit_index start, bit_index end, int symbol);
void citdSetAll(cit_ptr var, int symbol);
void citClean(cit_ptr var);
void citCleans(size_t number, cit_ptr lots, ...);

void citCopy(cit_ptr get, cit_ptr var, bit_index start, bit_index end);
void citdCopy(cit_ptr get, cit_ptr var);
void citFlip(cit_ptr get, cit_ptr var, bit_index start, bit_index end);
void citdFlip(cit_ptr get, cit_ptr var);
void citAnd(cit_ptr get, cit_ptr foo, cit_ptr bar, bit_index start, bit_index end);
void citOr(cit_ptr get, cit_ptr foo, cit_ptr bar, bit_index start, bit_index end);
void citXor(cit_ptr get, cit_ptr foo, cit_ptr bar, bit_index start, bit_index end);
void citdLogic(cit_ptr get, cit_ptr foo, cit_ptr bar, int signal);
void citdShift(cit_ptr get, cit_ptr var, uint64_t length, int signal);

void citShow(cit_ptr var, bit_index start, bit_index end, FILE * where);
void citdShow(cit_ptr var, bit_index start, bit_index end);

#endif
