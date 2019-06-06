# sieve of Eratosthenes

See this on [wikipedia](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes) to get more information.

## *quoted from wikipedia:* 

In mathematics, the Sieve of Eratosthenes is a simple, ancient algorithm for finding all prime numbers up to any given limit.

It does so by iteratively marking as composite (i.e., not prime) the multiples of each prime, starting with the first prime number, 2. The multiples of a given prime are generated as a sequence of numbers starting from that prime, with constant difference between them that is equal to that prime. This is the sieve's key distinction from using trial division to sequentially test each candidate number for divisibility by each prime.

One of a number of prime number sieves, it is one of the most efficient ways to find all of the smaller primes. It may be used to find primes in arithmetic progressions.

## My understanding

Suppose we want to find prime numbers under N. As you see, we can use an array of `int` to do this job, if i is a prime, then `a[i]` is set to one, otherwise zero. At first, from 0 to N, all the elements of array is set to 1, and we set `a[0]`, `a[1]` to be zero, because they are not prime numbers. Then, we start at 2, which is a prime number. Because 2 is a prime number, 2 + 2 must not be a prime number, so we set `a[4]` to be 0, 2 + 2 + 2 is not, too, we set `a[6]` to be 0,2 + 2 + 2 + 2 is not....... and so on. When multiples of 2 under N are sorted out, we start to find a a[i] whose value is 1, and we do the same thing on it...... After all these jobs are done, the elements of array remains to be 1 are the prime numbers we want to find. That's how I understand this.

## Some improvement

We all know that `int32_t` has a range of -2147483648 to 2147483647, `int`'s range is much more than what we exactly need. So it is a good choice to use `char`, which is 1 byte and has a range of -128 to 127. However, we only need the number ONE and ZERO to judge whether a number is a prime number or not. What we really need is just one bit. You may think `_Bool` can take this job, but it exactly has the same size of `char`. So I need to write some code to manipulate the bit, that's why you can see this little tutorial now.

## My experience

I happened to meet this prime number finding question on [projecteular](https://projecteuler.net/problem=10).Without thinking twice, I wrote down this prime-test code:
```C
int isPrime(int n)
{
    int i;
    for(i = 2;i < n;i ++)
    {
        if(n % i == 0)
          break;
    }
    if(i == n)
        return 1;
    else
        return 0;
}
```

The time I spend to find the prime number under two million costed me about five minutes, which made me frustrated. Therefore I read other's codes in the forum. And I learned what is sieve.

## Comparison to C++'s `<bitset>`

In v0.3, the time my code costs is approximately three times more than the C++'s version, but in v0.4, I was surprised that my code is a little faster than C++'s version. You can try my code in your machine and test the result.


  


