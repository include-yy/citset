# citset v1.0

# A Small Implementation of &lt;bitset> in C

### Description

Small potable bits manipulation in C.

use an array of `uint8_t`,`uint16_t` , `uint32_t` or `uint64_t` as underlying data-type utilizing all bits in each word.

It is well debugged.

### Current status 

- basic operations, such as get the value of one bit, modify the value of one bit are well supported.
- bitwise operation, `and`, `or`, `xor`, `flip`, `shift` are supported.

### Design goals 

The main design goal of this small library is to be small, correct, self contained. Clarity of the code is highly valued.

### Notable features and omissions

- the biggest number of bits you can get at a time is 4294967295(0XFFFFFFFF) * 8, delimited by the max value of unsigned int, which is used by malloc().
- the default array used by this library is `uint32_t`, if you want to modify it to something else, please go to the header file `cit_def.h` in v1.0/include and change the definition of CIT_WORD_SIZE to 1, 2 or 8(the default value is 4).

### API

This is the data-structure.
```C
typedef struct
{
  uint64_t _cit_alloc;
  size_t _cit_size;
  void * _cit_limb;
}cit_in;

typedef cit_in * cit_ptr;
typedef cit_in cit[1];
```
There are some macros.
```C
#define ONE              0X1
#define ZERO             0X0

#define AND              0X0
#define OR               0X1
#define XOR              0X2

#define LEFT             0X0
#define RIGHT            0X1
```
There are public APIs:
```C
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
```

### Usage

- go to v1.0, run `make` and `make clean` to get the static library `libcitset.a`, if you want the dynamic library, please run `make SHARE` and `make clean` to get `libcitset.so`. 
- if make doesn't work well, you can try again by using `makefile-vice`. run `make -f makefile-vice` to get `libcitset.a`, and run `make -f makfile-vice SHARE` to get `libcitset.so`.
- if you want to test them, run `make -f makefile-test` to test them one by one.
- if you are not on Linux, please use Mingw.
- if something unexpected happen, please contact me in the Issues.

### Examples 
- See [Example](https://github.com/include-yy/citset/tree/master/Example) for an example of how to calculate prime numbers by using sieve of Eratosthenes.

### More Information
- To get more information about how to use this little library and more details, read the [tutorial](https://github.com/include-yy/citset/blob/master/tutorial.md)
