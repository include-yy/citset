citset : tutorial
===

### [Descriptions](#1.0)
### [APIs](#2.0)

<h2 id = "1.0"> </h2>

### Descrpitions
- For clearity, I will use the `uint8_t` as unit, whose corresponding `CIT_WORD_SIZE` is 1.
- The index is start at zero(0).
- The order of bits is assumed to be increasing from left to right, not from right to left. The two graphs below show this point.
```
    +---+---+---+---+---+---+---+---+          +---+---+---+---+---+---+---+---+
YES | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |       NO | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | 
    +---+---+---+---+---+---+---+---+          +---+---+---+---+---+---+---+---+
```
The first thing we care about bit operation is that what we should do to get and set one bit of a unit.

Such as change the 6th bit of 01110010 to be 0, get the 4th bit of 01110010, which is 0.

C programming Language has provided us with &, |, ~, <<| and >>. It is a good idea to take full advantage of them.

to change the 6th bit of 01110010, we can do these in order.
- first, shift 01110010 left 6 bits, we can get 10000000,
- 10000000 & 10000000, now we can get 10000000, then, 
- we shift 10000000 right 7 bits, so we get 00000001, which is one.

In this example, the second 10000000 used in the second action is called [*Most significant bit*](https://en.wikipedia.org/wiki/Bit_numbering#Most_significant_byte), it can be used to judge the state of one bit. We call it MSB.

Now, we can describe the get operation as below: if we want the nth bit of an unit
- first, shift unit left (n - 1) bits, 
- and use the result to do like this: result & MSB
- then, we shift the result-2 right ((Number of bit of an unit) - 1) to get the final result.

So, how can we set one bit of an unit? Let's take 01110010 as example again, change the 4th bit to be 1.
- first, shift MSB right 4 bits, so we get 00001000,
- then, conduct 00001000 | 01110010, so we get 01111010.

It is also easy to change the 6th bits to be 0:
- first, shift MSB right 6 bits, so we get 00000010,
- then, flip 00000010 to get 11111101, then conduct 11111101 & 01110010.

Now, we have a good command of the basic operation. We can concate units to get bigger object, like this:
``` 
      unit 0    |     unit 1    |    ...
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|0|1|2|3|4|5|6|7|0|1|2|3|4|5|6|7|0|1|2|.......
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```
The index is allowed to be bigger than 7, how can we determine the exact place by using the index?
For expmple, we have the index 15, we can conduct 15 / 8 = 1, and 15 % 8 = 7. So the exact place is unit 1, bits 7.

it can be written as (1 . 7). The exact place of index 16 is (2 . 0).

We can define UNITBITS to be 8, which is number of bit in uint8_t, so we can describe this as below:
```
unit_index = index / UNITBITS;
bit_index = index % UNITBITS;
```

<h2 id = "2.0"> </h2>

### APIs

Here are some details about public api, which concerns about their definition, usage, and hint.

- [citInit()](#2.1)
- [citInits()](#2.2)
- [citGet()](#2.3)
- [citSet()](#2.4)
- [citSetAll()](#2.5)
- [citdSetAll()](#2.6)
- [citClean()](#2.7)
- [citCleans()](#2.8)
- [citCopy()](#2.9)
- [citdCopy()](#2.10)
- [citFlip()](#2.11)
- [citdFlip()](#2.12)
- [citAnd()](#2.13)
- [citOr()](#2.14)
- [citXor()](#2.15)
- [citdLogic()](#2.16)
- [citdShift()](#2.17)
- [citShow()](#2.18)
- [citdShow()](#2.19)

<h2 id = "2.1"> </h2>

``` C
void citInit(cit_ptr var, uint64_t total, int symbol);
```
Description:

this function accept three arguments, `var`, `total` and `symbol`.

the argument var's type is cit_ptr, you can declear a variable like this:
``` C
cit new;
```
the argument `total` means the number of bits you need. It can't be negative.

Note that it can't be bigger than (0XFFFFFFFF) * 8, because of the delimitation of malloc().

the argument `symbol` means the state of each bit, it can be either ONE or ZERO.

Usage:

``` C
cit new, old;
citInit(new, 16, ZERO);
citInit(old, 32, ONE);
citClean(new), citClean(old);
```
After this statements executed, `new` represents the bit object 0000 0000 0000 0000, and `old` represents 1111 1111 1111 1111 1111 1111 1111 1111.

Hint:

Notice that if `total` is not an integral multiple of CIT_WORD_SIZE * CHAR_BIT(if CIT_WORD_SIZE is 4, the value is 32), the actual allocated memory still be the integral mutiple of this lengthy value.

<h2 id = "2.2"> </h2>

``` C
void citInits(uint64_t total, int symbol, size_t number, cit_ptr lots, ...);
```
Description:

the funciton citInits() accept `total`, `symbol`, `number`, and any number of `cit_ptr` lots.

this function is just an extension of `citInit()`, which allows mutiple initialization at a time. The initialization to all the var is same.

the argument `number` specify the number of var need to be initializeed.

Usage：
``` C
cit new, old;
citInits(16, ONE, 2, new, old);
citCleans(2, new, old);
```
the result is : new : 1111 1111 1111 1111, old : 1111 1111 1111 1111

<h2 id = "2.3" > </h2>

``` C
size_t citGet(cit_ptr var, uint64_t index);
```
Description:

the function citGet() accept `var`, `index` as argument.

`var` specify an object to be got.

`index` tells citGet() which bit to get

Usage:

``` C
cit new;
citInit(new, 8, ONE);
int i;
for (i = 0; i < 8; i++)
    printf("%u",citGet(new, i));
citClean(new);
```

The output is 11111111.

Hint: 

citShow() depends on this function.

<h2 id = "2.4"> </h2>

``` C
void citSet(cit_ptr var, uint64_t index, int symbol);
```
Description: 

the function citSet() accept `var`, `index` and `symbol` as argument.

`symbol` determines the state of one bit will be set.

Usage:
``` C
cit new;
citInit(new, 8, ONE);
citSet(new, 0, ZERO);
citSet(new, 7, ZERO);
int i;
for (i = 0; i < 8; i++)
    printf("%u",citGet(new, i));
citClean(new);
```
The output is 01111110

<h2 id = "2.5"> </h2>

``` C
void citSetAll(cit_ptr var, uint64_t start, uint64_t end, int symbol);
```
Description:

the funciton citSetAll() accepts four argument.

`start` and `end` means the start index and end index to be set to symbol

Usage :
``` C
cit new;
citInit(new, 8, ONE);
citSetAll(new, 2, 5, ZERO);
int i;
for (i = 0; i < 8; i++)
    printf("%u",citGet(new, i));
citClean(new);
```
The output is 11000011

Hint :
citSetAll() and citdSetAll() have no connection.

<h2 id = "2.6"> </h2>

``` C
void citdSetAll(cit_ptr var, int symbol);
```
Description :

citdSetAll() accepts two arguments.

Unlike citSetAll, citdSetAll() will set all the bits of var to be symbol.

Usage :
``` C
cit new;
citInit(new, 8, ONE);
citdSetAll(new, ZERO);
int i;
for (i = 0; i < 8; i++)
    printf("%u",citGet(new, i));
citClean(new);
```
The output is 00000000

<h2 id = "2.7"> </h2>

``` C
void citClean(cit_ptr var);
```
Description :

citClean() will free the heap memory owned by var.

<h2 id = "2.8"> </h2>

``` C
void citCleans(size_t number, cit_ptr lots, ...);
```
Description :

citCleans() is just an extension of citClean(), which allows `Clean` lots of var at a time.

argument `number` specify the number of var to be free.

<h2 id = "2.9"> </h2>

``` C
void citCopy(cit_ptr get, cit_ptr var, uint64_t start, uint64_t end);
```
Description :

the argument `get` will get the result of the copy value of `var`.

`start` and `end` specify the start index and end index of bits needed to copy.

Usage :
``` C
cit new;
citInit(new, 8, ONE);
cit old;
citInit(old, 8, ZERO);
citCopy(new, old, 1, 4);
citdShow(new, 0, 7);
citCleans(2, old, new);
```
The output is 1000 0111

Hint : 

the two argument `get` and `var` must have the same number of bits. in the example above, `new` and `old` have the same number of bits, which is 8.

<h2 id = "2.10"> </h2>

``` C
void citdCopy(cit_ptr get, cit_ptr var);
```
Description :

unlike citCopy(), citdCopy will use all the bits of `get` and `var`

Usage :
``` C
cit new;
citInit(new, 8, ONE);
cit old;
citInit(old, 8, ZERO);
citdCopy(new, old)
citdShow(new, 0, 7);
citCleans(2, old, new);
```
The output is 0000 0000

Hint :

two arguments `get` and `var` must have the same number of bits.

<h2 id = "2.11"> </h2>

``` C
void citFlip(cit_ptr get, cit_ptr var, uint64_t start, uint64_t end);
```
Description :

citFlip will flip(~) the bit of `var` from `start` index to `end` index, and passes this part to `get`

Usage :

``` C
cit new;
citInit(new, 8, ONE);
cit old;
citInit(old, 8, ONE);
citFlip(new, old, 1, 3);
citdShow(new, 0, 7);
citCleans(2, old, new);
```
The output is 1000 1111

Hint :

two arguments `get` and `var` must have the same number of bits.    

<h2 id = "2.12"> </h2>

``` C
void citdFlip(cit_ptr get, cit_ptr var);
```

Description : 

unlike citFlip, citdFlip will flip all the bits of `var`, and passes it to `get`.

Usage :
``` C
cit new;
citInit(new, 8, ONE);
cit old;
citInit(old, 8, ONE);
citdFlip(new, old);
citdShow(new, 0, 7);
citCleans(2, old, new);
```
The putput is 0000 0000

Hint :

two arguments `get` and `var` must have the same number of bits.  

<h2 id = "2.13"> </h2>

``` C
void citAnd(cit_ptr get, cit_ptr foo, cit_ptr bar, uint64_t start, uint64_t end);
```
Description :

citAnd will `and`(&) the bit of `foo` and `bar` from `start` index to `end` index, and passes this part to `get`

Usage :
``` C
cit new, old;
citInit(new, 8, ONE);
citInit(old, 8, ONE);
cit now;
citInit(now, 8, ZERO);
citAnd(now, new, old, 1,2);
citdShow(now, 0, 7);
citCleans(3, old, new, now);
```
The output is 0110 0000

Hint :

three arguments `get`,`foo` and `var` must have the same number of bits.

<h2 id = "2.14"> </h2>

``` C
void citOr(cit_ptr get, cit_ptr foo, cit_ptr bar, uint64_t start, uint64_t end);
```
Description :

ciOr will `or`(|) the bit of `foo` and `bar` from `start` index to `end` index, and passes this part to `get`.

Usage :
``` C
cit new, old;
citInit(new, 8, ZERO);
citInit(old, 8, ONE);
cit now;
citInit(now, 8, ZERO);
citOr(now, new, old, 1,3);
citdShow(now, 0, 7);
citCleans(3, old, new, now);
```
The output is 0111 0000

Hint :

three arguments `get`,`foo` and `var` must have the same number of bits.

<h2 id = "2.15"> </h2>

``` C
void citXor(cit_ptr get, cit_ptr foo, cit_ptr bar, uint64_t start, uint64_t end);
```
Description :

citXor will `xor`(^) the bit of `foo` and `bar` from `start` index to `end` index, and passes this part to `get`.

Usage :
``` C
cit new;
citInit(new, 8, ONE);
citXor(new, new, new, 0, 3);
citdShow(new, 0, 7);
citClean(new);
```
The output is 0000 1111

Hint :

three arguments `get`,`foo` and `var` must have the same number of bits.

<h2 id = "2.16"> </h2>

``` C
void citdLogic(cit_ptr get, cit_ptr foo, cit_ptr bar, int signal);
```
Description: 

unlike `citAnd()`, `citOr()` and `citXor()`, `citdLogic()` will operate on all the bit of `foo` and `bar`

what `citdLogic()` will do depends on the argument `signal`, which can be `AND`, `OR` and `XOR`.

Usage :
``` C
cit new, old, now;
citInits(8, ONE, 2, new, old);
citInit(now, 8, ZERO);
citdLogic(now, new, old, AND);
citdShow(now, 0, 7), putchar('\n');
citdLogic(now, new, old, XOR);
citdShow(now, 0, 7), putchar('\n');
citdLogic(new, now, old, OR);
citdShow(new, 0, 7), putchar('\n');
citCleans(3, new, old, now);
```
The output is 

1111 1111

0000 0000

1111 1111

Hint :

three arguments `get`,`foo` and `var` must have the same number of bits.

<h2 id = "2.17"> </h2>

``` C
void citdShift(cit_ptr get, cit_ptr var, uint64_t length, int signal);
```
Description :

`citdShift()` will shift all the bit left or right, depending on the value of signal, which can be `LEFT` and `RIGHT`

the steps depends on `length`

Usage :
``` C
cit new;
citInit(new, 8, ONE);
citdShift(new, new, 4, LEFT);
citdShow(new, 0, 7), putchar('\n');
citdShift(new, new, 4, RIGHT);
citdShow(new, 0, 7), putchar('\n');
citClean(new);
```
The output is 

1111 0000

0000 1111

Hint :

two arguments `get` and `var` must have the same number of bits.

<h2 id = "2.18"> </h2>

``` C
void citShow(cit_ptr var, uint64_t start, uint64_t end, FILE * where);
```
Description :

`citShow()` will display the bits from start index to end index.

the FILE pointer `where` determine the place where the output go.

<h2 id = "2.19"> </h2>

``` C
void citdShow(cit_ptr var, uint64_t start, uint64_t end);
```
Description :

it is almost the same as `citShow()`, except the FILE pointer is `stdout`



