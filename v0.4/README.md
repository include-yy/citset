# citset

# A Small Implementation of &lt;bitset> in C

### Description

Small potable bits manipulation in C.

use an array of `uint8_t`,`uint16_t` or `uint32_t` as underlying data-type utilizing all bits in each word.

### Current status 

Basic operation, such as get the value of one bit, modify the value of one bit are supported, and the bitwise operation(&, |, ^, <<, >>) are also supported.

### Design goals 
The main design goal of this small library is to be small, correct, self contained. Clarity of the code is highly valued.

### Notable features and omissions
- the biggest number of bits you can get at a time is 4294967295(0XFFFFFFFF), delimited by the max value of unsigned int.
- it is mostly functional.

### API
This is the data-structure used, where CIT_UNIT is `#define`d to `uint8_t`,`uint16_t`or`uint32_t`.
```C
typedef struct
{
  unsigned int _cit_alloc;
  unsigned int _cit_size;
  CIT_UNIT * _cit_limb;
}cit;
```
This is public API:
```C
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
```

### Usage
Set `CIT_WORD_SIZE`in`citset.h`to {1, 2, 4} to determine the size of WORD_SIZE you use.

### Examples 
- See [v0.4/tests](https://github.com/include-yy/citset/tree/master/v0.4/tests) for some examples.
- See [Example](https://github.com/include-yy/citset/tree/master/Example) for an example of how to calculate prime numbers by using sieve of Eratosthenes.

### More Information
- To get more information about how to use this little library and more details, read the [tutorial](https://github.com/include-yy/citset/blob/master/tutorial.md)
