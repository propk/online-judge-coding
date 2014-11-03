#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<stdio.h>
#include<cstdio>
#include <algorithm>
#include <cmath>
#include <cstdlib>

//#define pc(x) putchar_unlocked(x);
#define LIMIT 100000000    // 10^8
#define MAX 10000  // sqrt(LIMIT)
#define segment_size 32768  // L1D_CACHE_SIZE

using namespace  std;

//inline void writeInt (int n)
//{
//    int N = n, rev, count = 0;
//    rev = N;
//    if (N == 0) { pc('0'); pc('\n'); return ;}
//    while ((rev % 10) == 0) { count++; rev /= 10;} //obtain the count of the number of 0s
//    rev = 0;
//    while (N != 0) { rev = (rev<<3) + (rev<<1) + N % 10; N /= 10;}  //store reverse of N in rev
//    while (rev != 0) { pc(rev % 10 + '0'); rev /= 10;}
//    while (count--) pc('0');
//}

void seg_sieve()
{
	int s = 2, n = 3;

	vector<char> small_primes(MAX + 1, 1); // flag for primes less than MAX
	vector<char> sieve(segment_size); // flag for primes in a segment

	// sieving small primes upto sqrt LIMIT
	for (int i = 2; i*i <= MAX; i++)
		if (small_primes[i])
			for (int j = i*i; j <= MAX; j += i)
				small_primes[j] = 0;

	vector<int> primes; // primes less than sqrt(high) of the present segment
	vector<int> next; // offset of the corresponding primes from vector primes in the next segment
	
	int k = 101,count = 1;
	for (int low = 0; low <= LIMIT; low += segment_size)
	{
		int high = (low + segment_size - 1) < LIMIT ? (low + segment_size - 1) : LIMIT;

		// storing small primes required to sieve the current segment
		for (; s*s <= high; s++)
		{
			if (small_primes[s])
			{
				primes.push_back((int)s);
				next.push_back((int)(s*s - low));
			}
		}

		fill(sieve.begin(), sieve.end(), 1); // initiallizing allcandidate flags to 1
		//sgmenting the current sieve
		for (size_t i = 1; i < primes.size(); i++)
		{
			int j = next[i];
			int increment = primes[i] * 2; // avoiding check for even primes
			for (; j < segment_size; j += increment)
				sieve[j] = 0;  // flagged not prime
			next[i] = j - segment_size;
		}

		// storing the primes
		for (; n <= high; n += 2)
        {   if (sieve[n - low])
            // n is a prime
            {
                count++;
                if(count == k)
                {
                    printf("%d",n);
                    //writeInt(n);
                    putchar('\n');
                    k +=100;
                }
            }
        }
	}
}

int main()
{
	cout<<2<<endl;
	seg_sieve();
	return 0;
}
