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

In this example, the second 10000000 used in the second action is called [*Most significant bit*](https://en.wikipedia.org/wiki/Bit_numbering#Most_significant_byte), it can be used to judge the state of one bit. We call is MSB.

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

Here are some details about public api, which concerns about their definition, use, and hint.

```

