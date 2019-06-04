#include<stdlib.h>
#include<limits.h>
#include<stdio.h>
typedef void* cit;
#define ZERO 0
#define ONE 1
#define HeadPointer sizeof(unsigned int )
  
cit citInit(unsigned int total,int signal)
{
  unsigned int bytes=total/sizeof(char);
  int i;
  unsigned int * headp=NULL;
  char * perm=NULL;
  cit varm;
  if(!total%sizeof(char))
    {
      varm=malloc(HeadPointer+bytes);
    }
  else
    {
      varm=malloc(HeadPointer+bytes+1);
      bytes++;
    }
  if(!varm)
    {
      puts("allocate error!");
      exit(EXIT_FAILURE);
    }
  headp=varm;
  *headp=total;
  varm=varm+sizeof(unsigned int);
  perm=varm;
  if(signal==ONE)
    {
      for(i=0;i<bytes;i++)
	perm[i]=UCHAR_MAX;
    }
  else if(signal==ZERO)
    {
      for(i=0;i<bytes;i++)
	perm[i]=ZERO;
    }
  else
    {
      puts("arguments error!");
      exit(EXIT_FAILURE);
    }
  return varm;
}

unsigned int citSize(cit varm)
{
  unsigned int * pnum=varm-sizeof(unsigned int);
  return *pnum;
}

unsigned int* citTell(cit varm,unsigned int index)
{
  unsigned int total=citSize(varm);
  if(index>=total)
    return NULL;
  unsigned int *p=malloc(sizeof(unsigned int)*2);
  if(!p)
    {
      puts("arguments error!");
      exit(EXIT_FAILURE);
    }
  p[0]=index/CHAR_BIT+1;
  p[1]=index%CHAR_BIT+1;
  return p;
}

int citGet(cit varm,unsigned int index)
{
  char *per=varm;
  unsigned int size=citSize(varm);
  if(index>=size)
    return -1;
  unsigned int *p=citTell(varm,index);
  per+=p[0]-1;
  size=((*per<<(p[1]-1))&0X80)>>7;
  free(p);
  return size;
}
  
void citSet(cit varm,unsigned int index,unsigned int signal)
{
  char *per=varm;
  unsigned int size=citSize(varm);
  if(index>=size)
    {
      puts("the second argument error!");
      exit(EXIT_FAILURE);
    }
  unsigned int *p=citTell(varm,index);
  per+=p[0]-1;
  if(signal==ONE)
    {
      *per|=(0X80>>(p[1]-1));
    }
  else if(signal==ZERO)
    {
      *per&=(~(0X80>>(p[1]-1)));
    }
  else
    {
      puts("the third argument error!");
      exit(EXIT_FAILURE);
    }
  free(p);
}

unsigned int citCount(cit varm)
{
  unsigned int size=citSize(varm);
  int i;
  unsigned int sum=0;
  for(i=0;i<size;i++)
    {
      if(citGet(varm,i))
	sum++;
    }
  return sum;
}

void citFlip(cit varm,unsigned int index)
{
  unsigned int value=citSize(varm);
  if(value>=index)
    {
      puts("amount error!");
      exit(EXIT_FAILURE);
    }
  value=citGet(varm,index);
  if(value)
    {
      citSet(varm,index,ZERO);
    }
  else
    {
      citSet(varm,index,ONE);
    }
}

void citFlipa1(cit varm)
{
  unsigned int size=citSize(varm);
  unsigned int bytes=size%8?size/8+1:size/8;
  char *now=varm;
  int i;
  for(i=0;i<bytes;i++)
    {
      *now=~*now;
      now++;
    }
}

void citShow(cit varm,unsigned int items,FILE *where)
{
  unsigned int size=citSize(varm);
  if(items>size)
    {
      puts("amount error!");
      exit(EXIT_FAILURE);
    }
  int i;
  for(i=0;i<items;i++)
    {
      putc(citGet(varm,i)+'0',where);
    }
}

void showbit(unsigned char ch,int n)
{
  int i;
    
  for(i=0;i<n;i++)
    {
      printf("%d",(ch&128)>>7);
      ch<<=1;
    }
}

void printbit(cit bit)
{
  int n=citSize(bit);
  char * now=bit;
  if(n%8==0)
    {
      int i=n/8;
      for(;i>0;i--)
	{
	  showbit(*now,8);
	  now++;
	}
    }
  else
    {
      int i=n/8;
      for(;i>0;i--)
	{
	  showbit(*now,8);
	  now++;
	}
      i=n/8;
      i=n-i*8;
      showbit(*now,i);
    }
}
