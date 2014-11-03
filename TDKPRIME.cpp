#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<stdio.h>
#include<cstdio>
#include <algorithm>
#include <cmath>
#include <cstdlib>

#define gc getchar_unlocked  // activate to use fast (but unsafe - unlocked stream) i/o
#define LIMIT 100000000    // 10^8
#define MAX 10000  // sqrt(LIMIT)
#define segment_size 32768  // L1D_CACHE_SIZE

using namespace  std;

// activate for fast i/o
void scanint(int &x) // unsigned integer
{
	register int c = gc();
	x = 0;
	for (; (c<48 || c>57); c = gc());
	for (; c>47 && c<58; c = gc()) {
    x = (x << 1) + (x << 3) + c - 48; 
  }
}

vector<long> all_primes; // storing all the primes less than LIMIT
void seg_sieve()
{
	int s = 2, n = 3;

	all_primes.push_back(2);
	vector<char> small_primes(MAX + 1, 1); // flag for primes less than MAX
	vector<char> sieve(segment_size); // flag for primes in a segment
	
	// sieving small primes upto sqrt LIMIT
	for (int i = 2; i*i <= MAX; i++)
		if (small_primes[i])
			for (int j = i*i; j <= MAX; j += i)
				small_primes[j] = 0;

	vector<int> primes; // primes less than sqrt(high) of the present segment
	vector<int> next; // offset of the corresponding primes from vector primes in the next segment

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
			if (sieve[n - low])
				all_primes.push_back(n);  // n is a prime
	}
}

int main()
{
	seg_sieve();
	int Q;
	cin >> Q;
	while (Q--)
	{
		int n;
		scanint(n);   // for fast i/o
 		//scanf("%ld", &n);
		cout << all_primes[n - 1] << endl;
	}
	return 0;
}
