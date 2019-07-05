#include <iostream>
#include <bitset>
#define TAX 10000000
using namespace std;

#include<time.h>
void Me(void)
{
  static int i = 0;
  static clock_t m;
  if(i == 0)
    {
      m =  clock();
      i = 1;
    }
  else if(i == 1)
    {
      printf("\ntime:%u\n",clock() - m);
      i = 0;
    }
}

int main(int argc, char **argv)
{
  bitset<TAX> Sieve;
   __int64 sum = 0;
        
   Sieve.flip();      // Set all bits to 1
   Sieve[0].flip();   // Set 0 and 1 to not prime
   Sieve[1].flip();
   // Check all nos from 2 to 1 million
   Me();
   for(long i = 2; i < TAX; ++i)
   {
      if( ! Sieve[i] )   // If marked not prime
         continue;      // return to head of loop
      else
         // Set all multiples as not prime
         for(long j = 2*i; j < TAX; j += i)
            Sieve[j] = 0; 
   }
   Me();
   for(long i = 2; i < TAX; ++i)
      if( Sieve[i] )   // Add all nos with bit set
         sum += i;

   cout << "\nThe sum is : "  << sum << endl;

   return 0;
}
