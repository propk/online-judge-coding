#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<array>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<cstdio>
//#define gc getchar_unlocked   

#define MAX 10000  //65536
#define LIM 100    //256
#define segment_size 1563  //100032/64

using namespace  std;

// activate for fast i-o access (not for windows)
//void scanint(long &x) // unsigned integer
//{
//	register long c = gc();
//	x = 0;
//	for (; (c<48 || c>57); c = gc());
//	for (; c>47 && c<58; c = gc()) {
//    x = (x << 1) + (x << 3) + c - 48; 
//  }
//}

void markMultiples(bool *arr, long prime, long start, long end)
{
	for (long j = prime*prime; j <= end; j += prime)
		arr[j] = 1;
}

void markSegMultiples(bool *arr, long prime, long low, long high)
{	
	long i;
	for (i = prime*prime; i < low; i += prime);
	for (long j = i; j <= high; j += prime)
		arr[j - low] = 1;
}


vector<long> primes;
void sieve()
{
	bool is_prime[MAX + 1] = { 0 };
	bool pm[LIM + 1] = { 0 };
	const long limit = 1000000;
	
	//seiving primes upto sqrt limit -> 2^32
	for (long i = 2; i <= LIM; i++)
		if (!pm[i])
			markMultiples(pm, i, 0, LIM);
	for (long i = 2; i <= LIM; i++)
		if (!pm[i])
			markMultiples(is_prime, i, 0, MAX);

	//storing small primes in vector
	vector<int> small_primes;
	int count = 0;
	for (long i = 2; i <= MAX; i++){
		if (!is_prime[i]) {
		small_primes.push_back(i); primes.push_back(i);
		count++;
		}
	}
	long temp = count;
	cout << "small primes found " << count << endl;

	//segmented sieve
	bool seg[segment_size] = { 0 };
	for (long low = MAX + 1; low <= limit; low += segment_size)
	{
		long high = (segment_size + low - 1) < limit ? (segment_size + low - 1) : limit;

		for (int i = 0; i < segment_size; i++)
			seg[i] = 0;
		
		for (int i = 0; i < temp; i++)
			markSegMultiples(seg, small_primes[i], low, high);
			
		for (long j = low; j <= high; j++)
			if (!seg[j - low]) { primes.push_back(j); count++; }
	}
	cout << "found large primes " << count << endl;
}

int main()
{
	int Q; // total number of querries
	sieve();
	cin >> Q;
	while (Q--)
	{
		long n;
		//scanint(n);   // fast i/o
		scanf("%ld", &n);
		cout << primes[n - 1] << endl;
	}
	return 0;
}
