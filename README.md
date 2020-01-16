# citset v1.1

# A Small Implementation of \<bitset\> in C

### Description

Small potable bits manipulation in C, the smallest object you can manipulate is bit, not byte.

### Current status

- basic operation, such as getting the value of a bit, modifing the value of a bit are well supported.

- In comparsion to v1.0, this version doesn't provide functions to allocate or free memory, which memory block you want to operate on depends on yourself.

- Is is well debugged and runs currently on Windows, Linux(Ubuntu) and WSL.

### Design goals

The main design goal of this small library is to be small, correct, self contained. Clarity of the code is highly valued.

### Notable features and omissions

- These functions do nothing about overlap checking, which means that you should be really careful about overlap.

- The memory block is passed as `void*` to make sure that any type of object can be passed to these functions without arising a warning.

- As I will explain below, the behaviour of function `citGet` is a little subtle.  Please use it in the right way to prevent you from annoying bugs.

### API

These are public functions:

```c
unsigned char citGetBit(const void * bitfield, size_t index);
void citSetBit(void * bitfield, size_t index, int symbol);
void citFlipBit(void * bitfield, size_t index);

size_t citCount(const void * bitfield, size_t start, size_t end);

void citGet(void * get, void * bitfield, size_t get_s, size_t bit_s, size_t n);
void citSet(void * bitfield, size_t start, size_t end, int symbol);
void citFlip(void * bitfield, size_t start, size_t end);

void citShow(const void * bitfield, size_t start, size_t end);
```

These are macros.

```c
#define citBOB(n) ((((n) - 1) / 8) + 1)

#define hide8_citGetBit(p, i) \
    ((((*((unsigned char *)(p) + ((size_t)(i) / 8))) << ((size_t)(i) % 8)) & 0x80) >> 7)

#define hide8_citSetBit(p, i, b) \
    ((*((unsigned char *)(p) + (size_t)(i) / 8)) = ((*((unsigned char *)(p) + (size_t)(i) / 8)) ^ ((-(b) ^ (*((unsigned char *)(p) + (size_t)(i) / 8))) & (0x80 >> ((size_t)(i) % 8)))))

#define hide8_citFlipBit(p, i) \
    ((*((unsigned char *)(p) + ((size_t)(i) / 8))) = ((*((unsigned char *)(p) + ((size_t)(i) / 8))) ^ (0x80 >> ((size_t)(i) % 8))))
```

I'll illustrate each function and macro's facility at the end of README.

### Example

- In `v1.1/Example` , I present how to find the sum of prime numbers under 10000000 by using sieve of Eratosthenes. I write C and C++ to present the procedure. You can compare the time between them.(In my computer, without any optimition, my code runs nine times faster than C++ version using \<bitset\>. C : C++ = 100ms : 900ms)

- You can also see some funny examples in `v1.1\test` .

### Going Further

This small library depends heavily on another small library called [citunit](https://github.com/include-yy/citunit), which is also written by me. You can go to see more details about it.

### Illustration

Every funciton and macro starts with the prefix `cit`. You can see that some functions have arguments with the type of `size_t`, whose origin type may be `unsigned int` or `unsigned long long`. These argument must not be negative because of `unsigned` . Some functions have argument type `const void*`, which makes sure that the state of memory block will not be modified.

What's the meaning of "index" in this libaray? If we have a index `n` , it doesn't means the nth bytes or any other units in the memory block. It actually means (n + 1)th bit in the memory block(Yes, index startd at zero.). If one funciton has range arguments `start` and `end` , it means that this function will operate on memory block from (start + 1)th bit to (end)th bit.

Now let's start with Macros:

```c
#define citBOB(n) ((((n) - 1) / 8) + 1)
```

- `BOB` means "bytes of bits", its value is the smallest number of byte to contain `n` bits. 

- `n` must be a non-negative integer.

- For example, `citBOB(8)` is `1`, and `citBOB(9)` is `2`.

```c
unsigned char citGetBit(const void * bitfield, size_t index);
```

- `GetBit` means "Get the value of a bit with index `index` in the memory block `bitfield` ", its return value can either be ZERO or ONE.

- For example, let's assume `char a = 0x7e;` ,`citGetBit(&a, 0)` is `0`, `citGetBit(&a, 7)` is `0`.  

```c
#define hide8_citGetBit(p, i) \
    ((((*((unsigned char *)(p) + ((size_t)(i) / 8))) << ((size_t)(i) % 8)) & 0x80) >> 7)
```

- this macro has the same facility with `citGetBit` , but it is faster than `citGetbit` when it is needed to be called million times.

```c
void citSetBit(void * bitfield, size_t index, int symbol);
```

- `SetBit` means "set the bit with index `index` to `symbol` ".

- `symbol` can either be `0` or `1` .

- For example, let's assume `char a = 0x8f;`, then `citSetBit(&a, 0, 1)`, we'll get `a == 0xff`.

```c
 #define hide8_citSetBit(p, i, b) \

    ((*((unsigned char *)(p) + (size_t)(i) / 8)) = ((*((unsigned char *)(p) + (size_t)(i) / 8)) ^ ((-(b) ^ (*((unsigned char *)(p) + (size_t)(i) / 8))) & (0x80 >> ((size_t)(i) % 8)))))
```

- this macro has the same facility with `citSetBit` , but it is faster than `citSetbit` when it is needed to be called million times.

```c
void citFlipBit(void * bitfield, size_t index);
```

- `FlipBit` means "flip the bit with index `index`".

- For example, let's assume `char a = 0;` , then `citFlipBit(&a, 7)`, we'll get `a == 1`.

```c
#define hide8_citFlipBit(p, i) \
    ((*((unsigned char *)(p) + ((size_t)(i) / 8))) = ((*((unsigned char *)(p) + ((size_t)(i) / 8))) ^ (0x80 >> ((size_t)(i) % 8))))
```

- this macro has the same facility with `citFlipBit` , but it is faster than `citFlipbit` when it is needed to be called million times.

```c
size_t citCount(const void * bitfield, size_t start, size_t end);
```

- `Count` means "count the bits with value `1` from index `start` to `end` ".

- For example, let's assume `char a = 0x78;`, `citCount(&a, 0, 8)` is `4`.

```c
void citSet(void * bitfield, size_t start, size_t end, int symbol);
```

- `Set` means "Set bits from `start` to `end` to `symbol`".

- `symbol` can either be ZERO or ONE.

- For example, let's assume `char a = 0x00;`, `citSet(&a, 0, 8, 1)`, we'll get `a == 0xff`.

```c
void citFlip(void * bitfield, size_t start, size_t end);
```

- `Flip` means "Flip bits from `start` to `end` ".

- For example, let's assume `char a = 0xf0;`, `citFlip(&a, 0, 8)`, we'll get `a == 0x0f`.

```c
void citShow(const void * bitfield, size_t start, size_t end);
```

- `Show` means "display bits from `start to end`".

- every eight bit with a space.

- For example, let's assume `char a[3] = {0xef, 0xab, 0xcd};`, `citShow(a,0, 24)` we'll see `11101111 10101011 11001101` on the console screen.

```c
void citGet(void * get, void * bitfield, size_t get_s, size_t bit_s, size_t n);
```

_As I mentioned above_, this function's facility is a little subtle. So more illustrations are needed to make it clear.

This function has five arguments, `get` is the memory block that gets a string of bits from `bitfield`. `get_s` is the start index of `get`  to store the bits, `bit_s` is the start index of `set` to deliver bits.`n` is the number of bits needed to be passed.

It is possible to use this funciton on `bitfiled` itself, like this: `citGet(a, a, 0, 5, 2)`, the value of `a` is an valid address. But I am highly recommand you not to do like this.

For example, let's assume that a is the address of two bytes memory block. and its print form is `0000 1111 0000 1111`, what will happen if I do `citGet(a, a, 0, 4, 4)` ? You may guess it is `1111 1111 0000 1111`, yes, it is the right answer. But what is the value of `citGet(a, a, 4, 0, 4)` , you can try it on your computer and it is an unexpected result.

But Why? It concerns about the concrete implemention of `citGet`. After you read the source code of citGet.c in `v1.1\src\citGet.c`, you'll find that it is safe to "Get bits"  from left to right, not from right to left.   

#### Use this funciton with two entirely different memory block instead of the same is a good choice.
