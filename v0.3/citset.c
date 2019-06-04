#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<stdarg.h>

typedef char * cit;
typedef unsigned int CIT_AMOUNT;
typedef unsigned char CIT_UNIT;
typedef int cit_loop;

#define AND (int)0
#define OR (int)1
#define XOR (int)2
#define RIGHT (int)0
#define LEFT (int)1
#define ZERO (int)0
#define ONE (int)1
#define DONT (int)2
#define ON (int)1
#define OFF (int)0

#define UNIT_MAX ((CIT_UNIT)0XFFU)
#define HIGH_ORDER ((CIT_UNIT)(~(UNIT_MAX >> 1U)))
#define HEADFIELD sizeof(CIT_AMOUNT)
#define UNITFIELD sizeof(CIT_UNIT)
#define UNITBITS (UNITFIELD * (CHAR_BIT))

#define CIT_MIN(a, b) ((a) > (b) ? (b) : (a))
#define CIT_MAX(a, b) ((a) > (b) ? (a) : (b))
#define IndexCheck(var, index) do {			\
    if((index) >= citSize(var)) {			\
      fprintf(stderr, "index error!\n");		\
      exit(EXIT_FAILURE);				\
    }							\
  }while(0);
#define UnitCheck(var, unit) do {		\
    if((unit) >= citUnit(var, ZERO)){		\
      fprintf(stderr, "unit error!\n");		\
      exit(EXIT_FAILURE);			\
    }						\
  }while(0);
  
cit citInit(CIT_AMOUNT total, int symbol);
void citInits(CIT_AMOUNT total, int symbol, CIT_AMOUNT number, cit * lots, ...);
CIT_AMOUNT citSize(cit var);
CIT_AMOUNT citUnit(cit var, CIT_AMOUNT size);
CIT_AMOUNT * citTell(CIT_AMOUNT index);
CIT_AMOUNT citGet(cit var, CIT_AMOUNT index);
void citSet(cit var, CIT_AMOUNT index, int symbol);
void citSetAll(cit var, int symbol);
cit citCopy(cit * GetTheCopy, cit var);
void citClean(cit * var);
void citCleans(CIT_AMOUNT number, cit * lots, ...);
void citShow(cit var,CIT_AMOUNT items, FILE * where);

CIT_AMOUNT citCountOne(cit var);
cit citFlip(cit var, CIT_AMOUNT index, int side_effect);
cit citFlipAll(cit var, int side_effect);
cit citShift(cit var, CIT_AMOUNT length, int way, int side_effect);
cit citBit(cit * GetTheResult, cit first, cit second, int operator);

cit citInputStr(cit * GetString, char * str);
cit citInputUnit(cit  Getit, CIT_AMOUNT unitindex, CIT_UNIT compound);
  
cit citInit(CIT_AMOUNT total, int symbol)
{
  if(total == 0U) {
    fprintf(stderr, "citInit: total error!\n");
    exit(EXIT_FAILURE);
  }  
  cit var = NULL;
  cit_loop i;
  CIT_UNIT * ptr = NULL;
  CIT_AMOUNT NumberOfUnits = citUnit(NULL, total);
  
  var = (cit)malloc(HEADFIELD + NumberOfUnits * UNITFIELD);
  if(!var) {
    fprintf(stderr, "citInit: memory allocate error!\n");
    exit(EXIT_FAILURE);
  }
  (*(CIT_AMOUNT*)var) = total;
  var += HEADFIELD;
  ptr = (CIT_UNIT*)var;
  if(symbol == ONE)
    for(i = 0;i < NumberOfUnits;i++)
      ptr[i] = UNIT_MAX;
  else if(symbol == ZERO)
    for(i = 0;i < NumberOfUnits;i++)
      ptr[i] = (CIT_UNIT)ZERO;
  else if(symbol == DONT)
    ;
  else
    fprintf(stderr, "citInit: symbol error!\n");
    exit(EXIT_FAILURE);
  }
  return var;
}

void citInits(CIT_AMOUNT total, int symbol, CIT_AMOUNT number, cit * lots, ...)
{
  va_list lis;
  cit_loop i;
  cit * var = NULL;
  va_start(lis, lots);
  *lots = citInit(total, symbol);
  for(i = 0;i < number - 1;i++) {
    var = va_arg(lis, cit*);
    *var = citInit(total, symbol);
  }
  va_end(lis);
}

CIT_AMOUNT citSize(cit var)
{
  return *((CIT_AMOUNT*)(var - HEADFIELD));
}

CIT_AMOUNT citUnit(cit var, CIT_AMOUNT size)
{
  if(var != NULL)
    size = citSize(var);
  return (size - 1) / UNITBITS + 1;
}
    
CIT_AMOUNT * citTell(CIT_AMOUNT index)
{
  CIT_AMOUNT * ptr = (CIT_AMOUNT*)malloc(sizeof(CIT_AMOUNT)*2);
  
  if(!ptr) {
    fprintf(stderr, "citTell: memory allocate error!\n");
    exit(EXIT_FAILURE);
  }
  ptr[0] = index / UNITBITS;
  ptr[1] = index % UNITBITS;
  return ptr;
}

CIT_AMOUNT citGet(cit var, CIT_AMOUNT index)
{
  IndexCheck(var, index);
  CIT_UNIT * operate = (CIT_UNIT*)var;
  CIT_AMOUNT * place = citTell(index);
  CIT_AMOUNT result;
  
  result = ((*(operate + place[0]) << place[1]) & HIGH_ORDER) >> (UNITBITS - 1U);
  free(place);
  return result;
}

void citSet(cit var, CIT_AMOUNT index, int symbol)
{
  IndexCheck(var, index);
  CIT_AMOUNT * place = citTell(index);
  CIT_UNIT * compound = (CIT_UNIT*)var;
  
  compound += place[0];
  if(symbol == ONE)
    *compound |= (HIGH_ORDER >> place[1]);
  else if(symbol == ZERO)
    *compound &= (~(HIGH_ORDER >> place[1]));
  else {
    fprintf(stderr, "citSet: symbol error!\n");
    exit(EXIT_FAILURE);
  }
  free(place);
}

void citSetAll(cit var, int symbol)
{
  CIT_AMOUNT size = citSize(var);
  CIT_UNIT * ptr = (CIT_UNIT*)var;
  cit_loop i;
  
  size = citUnit(NULL, size);
  if(symbol == ONE)
    for(i = 0;i < size;i++)
      ptr[i] = UNIT_MAX;
  else if(symbol == ZERO)
    for(i = 0;i < size;i++)
      ptr[i] = (CIT_UNIT)ZERO;
  else {
    fprintf(stderr, "citSetAll: symbol error!\n");
    exit(EXIT_FAILURE);
  }
}

cit citCopy(cit * GetTheCopy, cit var)
{
  if(GetTheCopy == NULL) {
    CIT_AMOUNT size = citSize(var);
    cit new = citInit(size, ZERO);
  
    size = citUnit(NULL, size);
    memcpy(new - HEADFIELD, var - HEADFIELD, HEADFIELD + size * UNITFIELD);
    return new;
  }
  else {
    CIT_AMOUNT size1 = citSize(*GetTheCopy);
    CIT_AMOUNT size2 = citSize(var);
    CIT_AMOUNT unit1 = citUnit(NULL, size1);
    CIT_AMOUNT unit2 = citUnit(NULL, size2);
    CIT_UNIT * deal = (CIT_UNIT*)(*GetTheCopy);
    cit_loop i;
    
    if(unit1 >= unit2) {
      memcpy(*GetTheCopy, var, unit2 * UNITFIELD);
      for(i = unit2;i < unit1;i++)
	deal[i] = (CIT_UNIT)ZERO;
    }
    else {
      citClean(GetTheCopy);
      *GetTheCopy = citCopy(NULL, var);
    }
    return NULL;
  }
}

void citClean(cit * var)
{
  free(*var - HEADFIELD);
  *var = NULL;
}

void citCleans(CIT_AMOUNT number, cit * lots, ...)
{
  va_list lis;
  cit_loop i;
  cit * var;
  va_start(lis,lots);
  citClean(lots);
  for(i = 0;i < number - 1;i++) {
    var = va_arg(lis, cit*);
    citClean(var);
  }
  va_end(lis);
}
    
void citShow(cit var, CIT_AMOUNT items, FILE * where)
{
  CIT_AMOUNT size = citSize(var);
  cit_loop i;
  
  if(items > size) {
    fprintf(stderr,"citShow: items error!");
    exit(EXIT_FAILURE);
  }
  for(i = 0;i < items;i++) {
    putc(citGet(var, i) + '0', where);
    if((i + 1) % 4 == 0)
      putc(' ',where);
  }
}

CIT_AMOUNT citCountOne(cit var)
{
  CIT_AMOUNT size = citSize(var);
  cit_loop i;
  CIT_AMOUNT sum = 0L;
  
  for(i = 0;i < size;i++)
    if(citGet(var, i))
      sum++;
  return sum;
}

cit citFlip(cit var, CIT_AMOUNT index, int side_effect)
{
  IndexCheck(var,index);
  CIT_AMOUNT value = citGet(var,index);
  
  if(side_effect == ON) {
    citSet(var, index, value ? ZERO : ONE);
    return NULL;
  }
  else {
    cit new = citCopy(var);
    citSet(new, index, value ? ZERO : ONE);
    return new;
  }
}

cit citFlipAll(cit var, int side_effect)
{
  CIT_AMOUNT size = citSize(var);
  cit_loop i;
  CIT_UNIT * ptr;
  
  size = citUnit(NULL, size);
  if(side_effect == ON) {
    ptr = (CIT_UNIT*)var;
    for(i = 0;i < size;i++) {
      *ptr = ~*ptr;
      ptr++;
    }
    return NULL;
  }
  else {
    cit new = citCopy(NULL, var);
    ptr = (CIT_UNIT*)new;
    for(i = 0;i < size;i++) {
      *ptr = ~*ptr;
      ptr++;
    }
    return new;
  }
}

cit citShift(cit var, CIT_AMOUNT length, int way, int side_effect)
{
  CIT_AMOUNT size = citSize(var);
  cit_loop i;
  
  if(length >= size) {
    if(side_effect == ON) {
      citSetAll(var, ZERO);
      return NULL;
    }
    else {
      cit new = citInit(size, ZERO);
      return new;
    }
  }
  else {
    if(way == RIGHT) {
      if(side_effect == ON) {
	for(i = 0;i < size - length;i++)
	  citSet(var, i + length, citGet(var, i));
	for(i = 0;i < length;i++)
	  citSet(var, i, ZERO);
	return NULL;
      }
      else if(side_effect == OFF) {
	cit new = citInit(size, ZERO);
	for(i = 0;i < size - length;i++)
	  citSet(new, i + length, citGet(var, i));
	return new;
      }
    }
    else if(way == LEFT){
      if(side_effect == ON) {
	for(i = 0;i < size - length;i++)
	  citSet(var, i, citGet(var, i + length));
	for(i = size - length;i < size;i++)
	  citSet(var, i, ZERO);
	return NULL;
      }
      else if(side_effect == OFF) {
	cit new = citInit(size, ZERO);
	for(i = 0;i < size - length;i++)
	  citSet(new, i, citGet(var, i + length));
	return new;
      }
    }
  }
}

cit citBit(cit * GetTheResult, cit first, cit second,int operator)
{
  cit big, small, cross;
  CIT_AMOUNT units;
  CIT_UNIT * p = NULL;
  CIT_UNIT * q = NULL;
  cit_loop i;

  if(citSize(first) > citSize(second))
    big = first, small = second;
  else
    big = second, small = first;
  cross = citCopy(NULL, big), p = (CIT_UNIT*)cross, q = (CIT_UNIT*)small;
  units = citUnit(small, ZERO);
  if(operator == AND)
    for(i = 0;i < units;i++)
      p[i] &= q[i];
  else if (operator == OR) 
    for(i = 0;i < units;i++)
      p[i] |= q[i];
  else if (operator == XOR)
    for(i = 0;i < units;i++)
      p[i] ^= q[i];
  else {
    fprintf(stderr,"citBit: operator error!\n");
    exit(EXIT_FAILURE);
  }
  if(GetTheResult == NULL)
    return cross;
  else {
    citCopy(GetTheResult, cross);
    citClean(cross);
    return NULL;
  }
}

cit citInputStr(cit * GetString, char * str)
{
  CIT_AMOUNT length = strlen(str);
  CIT_AMOUNT size = citSize(*GetString);
  cit_loop i;
  if(GetString == NULL) {
    cit c = citInit(length,DONT);
    for(i = 0;i < length;i++) {
      if(str[i] == '0')
	citSet(c, i, ZERO);
      else
	citSet(c, i, ONE);
    }
    return c;
  }
  else {
    if(size >= length) {
      for(i = 0;i < length;i++)
	if(str[i] == '0')
	  citSet(*GetString, i, ZERO);
	else
	  citSet(*GetString, i, ONE);
      for(; i < size;i++)
	citSet(*GetString, i, ZERO);
    }
    else {
      citClean(GetString);
      *GetString = citInit(length, DONT);
      for(i = 0;i < length;i++)
	if(str[i] == '0')
	  citSet(*GetString, i, ZERO);
	else
	  citSet(*GetString, i, ONE);
    }
    return NULL;
  }
}

cit citInputUnit(cit Getit, CIT_AMOUNT unitindex, CIT_UNIT compound)
{
  if(Getit == NULL) {
    CIT_AMOUNT units = unitindex + 1;
    CIT_AMOUNT size = units * UNITBITS;
    cit c = citInit(size, ZERO);
    ((CIT_UNIT*)c)[unitindex] = compound;
    return c;
  }
  else {
    UnitCheck(Getit, unitindex);
    ((CIT_UNIT*)(Getit))[unitindex] = compound;
    return NULL;
  }
}

