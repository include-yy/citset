#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<stdarg.h>

#include"citset.h"

/* Memory allocation and other helper functions */
static void
cit_die (char * msg)
{
  fprintf(stderr, "%s\n", msg);
  abort();
}

static void *
cit_default_alloc (size_t size)
{
  void * p;

  p = malloc(size);
  if(!p)
    cit_die("cit_default_alloc: memory exhausted.");

  return p;
}

static void *
cit_default_realloc (void * old, size_t old_size, size_t new_size)
{
  void * p;

  p = realloc(old, new_size);
  if(!p)
    cit_die("cit_default_realloc: memory exausted.");

  return p;
}

static void
cit_default_free (void * p, size_t size)
{
  free(p);
}

static void * (*cit_allocate_func) (size_t) = cit_default_alloc;
static void * (*cit_reallocate_func) (void *, size_t, size_t) = cit_default_realloc;
static void (*cit_free_func) (void *, size_t) = cit_default_free;

#define cit_alloc(size) ((*cit_allocate_func)((size)))
#define cit_free(p) ((*cit_free_func) ((p), 0))

static cit_unit_ptr
cit_alloc_limb (unsigned int size)
{
  return (cit_unit_ptr)cit_alloc(size * sizeof (CIT_UNIT));
}

static cit_unit_ptr
cit_realloc_limb (cit_unit_ptr old, unsigned int size)
{
  return (cit_unit_ptr)(*cit_reallocate_func)(old, 0, size * sizeof(CIT_UNIT));
}

static void
cit_zerone (cit_unit_ptr p, unsigned int n, int signal)
{
  if(signal == ONE)
    {
      while(--n > 0)
	p[n] = -1;
      p[0] = -1;
    }
  else if(signal == ZERO)
    {
      while(--n > 0)
	p[n] = 0;
      p[0] = 0;
    }
  else
    cit_die("cit_zerone: signal error, which must be ONE or ZERO!\n");
}

static unsigned int cit_place[2];

static void
cit_tell (unsigned int index)
{
  cit_place[0] = index / UNITBITS;
  cit_place[1] = index % UNITBITS;
}

static unsigned int
cit_unit_get (cit_unit_ptr p, unsigned int index)
{
  return ((*p << index) & CIT_UNIT_MSB) >> (UNITBITS - 1);
}

static void
cit_unit_set (cit_unit_ptr p, unsigned int index, int symbol)
{
  if(symbol == ONE)
    {
      *p |= (CIT_UNIT_MSB >> index);
    }
  else if(symbol == ZERO)
    {
      *p &= (~(CIT_UNIT_MSB >> index));
    }
  else
    {
      cit_die("cit_unit_set: symbol error!\n");
    }
}

static void
cit_copy (cit_unit_ptr d, cit_unit_ptr s ,unsigned int n)
{
  unsigned int i;
  
  for(i = 0;i < n;i++)
    d[i] = s[i];
}

static void
cit_flip_with_assign (cit var)
{
  cit_unit_ptr ptr = var._cit_limb;
  unsigned int i;
  
  for(i = 0;i < var._cit_size;i++, ptr++)
    *ptr = ~*ptr;
}
  
static cit
cit_flip_no_assign (cit var)
{
  cit new = citCopy(var);
  
  cit_flip_with_assign(new);

  return new;
}

static void
cit_shift_left_with_assign (cit var, unsigned int length)
{
  unsigned int i;
  
  if(length >= var._cit_alloc)
    cit_zerone(var._cit_limb, var._cit_size, ZERO);
  else
    {
      for(i = 0;i < var._cit_alloc - length;i++)
	citSet(var, i, citGet(var, i + length));
      for(i = var._cit_alloc - length; i < var._cit_alloc;i++)
	citSet(var, i, ZERO);
    }
}

static cit
cit_shift_left_no_assign (cit var, unsigned int length)
{
  cit new = citCopy(var);
  
  cit_shift_left_with_assign(new, length);
  
  return new;
}

static void
cit_shift_right_with_assign (cit var, unsigned int length)
{
  unsigned int i;
  
  if(length >= var._cit_alloc)
    cit_zerone(var._cit_limb, var._cit_size, ZERO);
  else
    {
      for(i = var._cit_alloc - 1;i >= length;i--)
	citSet(var, i, citGet(var, i - length));
      for(i = 0;i < length;i++)
	citSet(var, i, ZERO);
    }
}

static cit
cit_shift_right_no_assign (cit var, unsigned int length)
{
  cit new = citCopy(var);
  
  cit_shift_right_with_assign(new,length);
  
  return new;
}
 
static cit
cit_and(cit first, cit second)
{
  unsigned int units = first._cit_size;
  unsigned int i;
  cit new = citCopy(first);
  
  cit_unit_ptr p = new._cit_limb;
  cit_unit_ptr q = second._cit_limb;

  for(i = 0;i < units;i++)
    {
      p[i] &= q[i];
    }
  return new;
}
      
static cit
cit_or(cit first, cit second)
{
  unsigned int units = first._cit_size;
  unsigned int i;
  
  cit new = citCopy(first);
  
  cit_unit_ptr p = new._cit_limb;
  cit_unit_ptr q = second._cit_limb;

  for(i = 0;i < units;i++)
    {
      p[i] |= q[i];
    }
  return new;
}

static cit
cit_xor(cit first, cit second)
{
  unsigned int units = first._cit_size;
  unsigned int i;
  
  cit new = citCopy(first);
  
  cit_unit_ptr p = new._cit_limb;
  cit_unit_ptr q = second._cit_limb;

  for(i = 0;i < units;i++)
    {
      p[i] ^= q[i];
    }
  return new;
}

#define IndexCheck(var, index) do {		\
    if((index) >= (var._cit_alloc))		\
      cit_die("index error!\n");		\
  }while(0);

#define UnitCheck(var, unit) do {		\
    if((unit) >= (var._cit_size))		\
      cit_die("unit error!\n");			\
  }while(0);

/* interface */
cit citInit(unsigned int total, int symbol)
{
  if(total == 0)
    cit_die("citInit: total error!\n");

  cit var = {0, 0, NULL};
  unsigned int NumOfUnit = (total - 1) / UNITBITS + 1;

  var._cit_alloc = total;
  var._cit_size = NumOfUnit;
  var._cit_limb = cit_alloc_limb(NumOfUnit);
  
  cit_zerone(var._cit_limb, NumOfUnit, symbol);
  
  return var;
}

void
citInits (unsigned int total, int symbol, unsigned int number, cit * lots, ...)
{
  va_list lis;
  unsigned int i;
  cit * var = NULL;
  
  va_start(lis, lots);
  *lots = citInit(total, symbol);
  
  for(i = 0;i < number - 1;i++)
    {
      var = va_arg(lis, cit*);
      *var = citInit(total, symbol);
    }
  va_end(lis);
}

unsigned int
citGet (cit var, unsigned int index)
{
  IndexCheck(var, index);
  cit_tell(index);
  
  cit_unit_ptr operator = var._cit_limb;
  
  operator += cit_place[0];

  return cit_unit_get(operator, cit_place[1]);
}

void
citSet (cit var, unsigned int index, int symbol)
{
  IndexCheck(var, index);
  cit_tell(index);
  
  cit_unit_ptr compound = var._cit_limb;
  
  compound += cit_place[0];
  cit_unit_set(compound, cit_place[1], symbol);

}

void citSetAll (cit var, int symbol)
{
  cit_zerone(var._cit_limb, var._cit_size, symbol);
}

cit
citCopy (cit old)
{
  cit new;
  
  new._cit_alloc = old._cit_alloc;
  new._cit_size = old._cit_size;
  new._cit_limb = cit_alloc_limb(old._cit_size);

  cit_copy(new._cit_limb, old._cit_limb, new._cit_size);

  return new;
}
  
void
citClean (cit * var)
{
  cit_free(var->_cit_limb);

  var->_cit_alloc = 0;
  var->_cit_size = 0;
  var->_cit_limb = NULL;
}

void
citCleans (unsigned int number, cit * lots, ...)
{
  va_list lis;
  unsigned int i;
  cit * var;

  va_start(lis, lots);
  citClean(lots);
  for(i = 0;i < number - 1;i++)
    {
      var = va_arg(lis, cit*);
      citClean(var);
    }
  va_end(lis);
}

cit citFlip (cit var, int assign)
{
  if(assign == ON)
    cit_flip_with_assign(var);
  else if(assign == OFF)
    return cit_flip_no_assign(var);
  else
    cit_die("citFlip: assign argument error, which must be ON or OFF!\n");
}

cit
citShift (cit var, int way, unsigned int length, int assign)
{
  if(way == LEFT)
    if(assign == ON)
      cit_shift_left_with_assign(var, length);
    else if(assign == OFF)
      return cit_shift_left_no_assign(var, length);
    else
      cit_die("citShift: assign argument error!\n");
  else if(way == RIGHT)
    if(assign == ON)
      cit_shift_right_with_assign(var, length);
    else if(assign == OFF)
      return cit_shift_right_no_assign(var, length);
    else
      cit_die("citShift: assign argument error!\n");
  else
    cit_die("citShift: way argument error!\n");
}

cit
citBit (cit first, cit second, int symbol)
{
  if(first._cit_alloc != second._cit_alloc)
    cit_die("citBit: the number of bits aren't equal!\n");
  if(symbol == AND)
    return cit_and(first,second);
  else if(symbol == OR)
    return cit_or(first,second);
  else if(symbol == XOR)
    return cit_xor(first, second);
  else
    cit_die("citBit: operator error!\n");
}

void
citfShow (cit var, unsigned int start, unsigned int end, FILE * where)
{
  IndexCheck(var, end);
  if(start > end)
    cit_die("citShow: start index bigger than end index");
  unsigned int i;
  for(i = start;i <= end;i++)
    {
      putc(citGet(var,i) + '0', where);
      if((i + 1) % 4 == 0)
	putc(' ',where);
    }
}

void
citShow (cit var, unsigned int start, unsigned int end)
{
  citfShow(var, start, end, stdout);
}

cit
citinStr (char * str)
{
  unsigned int i;
  unsigned int length = strlen(str);
  cit c = citInit(length,ONE);

  for(i = 0;i < length;i++)
    if(str[i] == '0')
      citSet(c, i, ZERO);
  return c;
}

void
citinUnit (cit Getit, unsigned int index, CIT_UNIT compound)
{
  UnitCheck(Getit, index);
  
  Getit._cit_limb[index] = compound;
}
