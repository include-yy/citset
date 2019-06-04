#include"citset.h"
cit citInit(SCALAR total, _Bool signal)
{
  SCALAR units = total / BitLength;
  SCALAR * headp = NULL;
  STDUNIT * perm = NULL;
  cit varm = NULL;
  loop_t i;
  if(!(total % BitLength))
    {
      varm = (cit)malloc(HeadField + units * BitLength / CHAR_BIT);
    }
  else
    {
      units++;
      varm = (cit)malloc(HeadField + units * BitLength / CHAR_BIT);
    }
  if(!varm)
    {
      puts("citInit: memory allocate error!");
      exit(EXIT_FAILURE);
    }
  headp = varm;
  *headp = total;
  varm += HeadField;
  perm = varm;
  if(signal == ONE)
    {
      for(i = 0;i < units;i++)
	{
	  perm[i] = STDUNIT_MAX;
	}
    }
  else if(signal == ZERO)
    {
      for(i = 0;i < units;i++)
	{
	  perm[i] = ZERO;
	}
    }
  return varm;
}

cit citStr(char * liter)
{
  SCALAR len = strlen(liter);
  cit new = citInit(len,ZERO);
  loop_t i;
  for(i = 0;i < len;i++)
    {
      if(liter[i] == '0')
	{
	  citSet(new, i, ZERO);
	}
      else
	{
	  citSet(new, i, ONE);
	}
    }
  return new;
} 
      
SCALAR citSize(cit varm)
{
  return *((SCALAR*)(varm - HeadField));
}

SCALAR* citTell(cit varm, SCALAR index)
{
  SCALAR * p = (SCALAR*)malloc(sizeof(SCALAR) * 2);
  if(!p)
    {
      puts("citTell: memory allocate error!");
      exit(EXIT_FAILURE);
    }
  p[0] = index / BitLength + 1;
  p[1] = index % BitLength + 1;
  return p;
}

SCALAR citGet(cit varm, SCALAR index)
{
  IndexCheck(varm, index);
  STDUNIT * per = varm;
  SCALAR * p = citTell(varm, index);
  SCALAR value;
  per +=( p[0] - 1);
  value = ((*per << (p[1] - 1)) & HIGH_ORDER) >> (BitLength - 1);
  free(p);
  return value;
}

void citSet(cit varm, SCALAR index, _Bool signal)
{
  IndexCheck(varm, index);
  STDUNIT * per =varm;
  SCALAR * p =citTell(varm, index);
  per += p[0] - 1;
  if(signal == ONE)
    {
      *per |= (HIGH_ORDER >> (p[1] - 1));
    }
  else if(signal == ZERO)
    {
      *per &= (~(HIGH_ORDER >> (p[1] - 1)));
    }
  free(p);
}

cit citCopy(cit varm)
{
  SCALAR size = citSize(varm);
  SCALAR units= size % BitLength? size / BitLength + 1: size / BitLength;
  cit new = citInit(size,ZERO);
  memcpy(new - HeadField, varm - HeadField, HeadField + units * BitLength / CHAR_BIT);
  return new;
}
  
void citClean(cit varm)
{
  varm -= HeadField;
  free(varm);
}

/*the basic part end*/

SCALAR citCount(cit varm)
{
  SCALAR size = citSize(varm);
  loop_t i;
  SCALAR sum = 0;
  for(i = 0;i < size;i++)
    {
      if(citGet(varm, i))
	sum++;
    }
  return sum;
}

void citFlip(cit varm, SCALAR index)
{
  IndexCheck(varm, index);
  SCALAR value = citGet(varm, index);
  citSet(varm, index, value? ZERO: ONE);
}

void citFlipa(cit varm)
{
  SCALAR size = citSize(varm);
  SCALAR units = size % BitLength? size / BitLength + 1: size / BitLength;
  STDUNIT * now = varm;
  loop_t i;
  for(i = 0;i < units;i++)
    {
      *now = ~*now;
      now++;
    }
}

cit citShift(cit varm, SCALAR dis, SCALAR way)
{
  SCALAR size = citSize(varm);
  cit new = citInit(size, ZERO);
  int i;
  if(way == RIGHT)
    {
      if(dis >= size)
	return new;
      else
	{
	  for(i = 0;i < size - dis;i++)
	    {
	      citSet(new, i + dis, citGet(varm, i));
	    }
	  return new;
	}
    }
  else if(way == LEFT)
    {
      if(dis >= size)
	return new;
      else
	{
	  for(i = 0;i < size - dis;i++)
	    {
	      citSet(new, i, citGet(varm, i + dis));
	    }
	  return new;
	}
    }
  else
    {
      puts("operator error!");
      exit(EXIT_FAILURE);
    }
}
	  
cit citBit(cit first, cit second,SCALAR op)
{
  cit big, small, cross;
  SCALAR units;
  STDUNIT * p, * q;
  loop_t i;
  if(citSize(first) > citSize(second))
    {
      big = first;
      small = second;
    }
  else
    {
      big = second;
      small = first;
    }
  cross = citCopy(big),p = cross,q = small;
  units = MIN(citSize(big),citSize(small));
  units = units % BitLength? units / BitLength + 1: units / BitLength;
  if(op == AND)
    {
      for(i = 0;i < units;i++)
	{
	  p[i] = p[i] & q[i];
	}
    }
  else if(op == OR)
    {
      for(i = 0;i < units;i++)
	{
	  p[i] = p[i] | q[i];
	}
    }
  else if(op == XOR)
    {
      for(i = 0;i < units;i++)
	{
	  p[i] = p[i] ^ q[i];
	}
    }
  else
    {
      puts("operator error!");
      exit(EXIT_FAILURE);
    }
  return cross;
}

void citShow(cit varm, SCALAR items, FILE *where)
{
  SCALAR size = citSize(varm);
  if(items > size)
    {
      puts("citShow: items error!");
      exit(EXIT_FAILURE);
    }
  loop_t i;
  for(i = 0;i < items;i++)
    {
      putc(citGet(varm, i) + '0', where);
      if((i + 1) % 4 == 0)
	putc(' ',where);
    }
}
